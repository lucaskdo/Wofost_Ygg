#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include "wofost.h"
#include "extern.h"


int main(int argc, char **argv)
{
    
    FILE **output;
    
    SimUnit *initial  = NULL;
    Weather *head;
      
    int CycleLength   = 300;
    int NumberOfFiles;
    int Emergence;
    
    char list[MAX_STRING];
    char meteolist[MAX_STRING];
    char name[MAX_STRING];
    
    Step = 1.;
    
    if (argc != 3) exit(0);
    if (strlen(argv[1]) >= MAX_STRING) exit(0);
    if (strlen(argv[2]) >= MAX_STRING) exit(0);
    
    memset(list,'\0',MAX_STRING);
    memset(meteolist,'\0',MAX_STRING);
    
    strncpy(list,argv[1],strlen(argv[1]));
    strncpy(meteolist,argv[2],strlen(argv[2]));
    
    /* Fill the crop, soil, site and management place holders*/
    NumberOfFiles = GetSimInput(list);
    
    /* Set the initial Grid address */
    initial = Grid;    
    
    /* Get the meteo filenames and put them in the placeholder */
    GetMeteoInput(meteolist);
    
    /* Allocate memory for the file pointers */
    output = malloc(sizeof(**output) * NumberOfFiles);
    
    /* Go back to the beginning of the list */
    Grid = initial;
    
    /* Open the output files */
    while (Grid)
    {   /* Make valgrind happy  */
        memset(name,'\0',MAX_STRING);
        strncpy(name, Grid->output,strlen(Grid->output));
           
        output[Grid->file] = fopen(name, "w");
        if(output[Grid->file] == NULL){
            fprintf(stderr, "Cannot initialize output file %s.\n", name);
            exit(0);
        }
        header(output[Grid->file]);
        Grid = Grid->next;
    }
    
    /* Go back to the beginning of the list */
    Grid = initial;
    
    
    while (Meteo)
    {
        /* Get the meteodata */
        if(GetMeteoData(Meteo) != 1) {
            fprintf(stderr, "Cannot get meteo data.\n");
            exit(0);
        }
        printf("running %d - %d\n", Meteo->StartYear, Meteo->EndYear);
        
        for (Lon = 0; Lon < Meteo->nlon; Lon++) {
            for(Lat = 0; Lat < Meteo->nlat; Lat++) {
                if(Mask[Lon][Lat] != 1){
                    continue;
                }
                
                fprintf(stdout, "Location: %lf N - %lf E\n", Latitude[Lat], Longitude[Lon]);
                
                for (Day = 0; Day < Meteo->ntime; Day++) //assume that the series start January first
                {                   
                    /* Go back to the beginning of the list */
                    Grid = initial;

                    /* Set the date struct */
                    memset(&current_date, 0, sizeof(current_date)); 
                    current_date.tm_year = MeteoYear[Day] -1900;
                    current_date.tm_mday =  0 + MeteoDay[Day];
                    mktime(&current_date);

                    while (Grid)
                    {
                        /* Get data, states and rates from the Grid structure and */
                        /* put them in the place holders */
                        Crop      = Grid->crp;
                        WatBal    = Grid->soil;
                        Mng       = Grid->mng;
                        Site      = Grid->ste;
                        //Start     = Grid->start;
                        Emergence = Grid->emergence; /* Start simulation at sowing or emergence */

                        Temp = 0.5 * (Tmax[Lon][Lat][Day] + Tmin[Lon][Lat][Day]);
                        DayTemp = 0.5 * (Tmax[Lon][Lat][Day] + Temp);

                        /* Only simulate between start and end year */
                        if ( MeteoYear[Day] >=  Meteo->StartYear && MeteoYear[Day] <= Meteo->EndYear)
                        {   
                            /* Determine if the sowing already has occurred */
                            IfSowing(Grid->start);

                            /* If sowing has occurred than determine the emergence */
                            if (Crop->Sowing >= 1 && Crop->Emergence == 0)
                            {
                                if (EmergenceCrop(Emergence))
                                {                 
                                    /* Initialize: set state variables */
                                    InitializeCrop();
                                    InitializeWatBal();
                                    InitializeNutrients(); 
                                }  
                            }

                            if (Crop->Sowing >= 1 && Crop->Emergence == 1)
                            {   
                                if (Crop->st.Development <= (Crop->prm.DevelopStageHarvest) && Crop->GrowthDay < CycleLength) 
                                {
                                    Astro();
                                    CalcPenman();
                                    CalcPenmanMonteith();

                                   /* Calculate the evapotranspiration */
                                    EvapTra();

                                    /* Set the rate variables to zero */
                                    RatesToZero();

                                     /* Rate calculations */
                                    RateCalulationWatBal();
                                    Partioning();
                                    RateCalcultionNutrients();
                                    RateCalculationCrop();

                                    /* Write to the output files */
                                    //Output(output[Grid->file]);   

                                    /* Calculate LAI */
                                    Crop->st.LAI = LeaveAreaIndex();             

                                    /* State calculations */
                                    IntegrationCrop();
                                    IntegrationWatBal();
                                    IntegrationNutrients();

                                    /* Update the number of days that the crop has grown*/
                                    Crop->GrowthDay++;
                                }
                                else
                                {
                                    /* Write to the output files */
                                    Output(output[Grid->file]);
                                    
                                    //printf("%7d %7d\n", MeteoYear[Day], Crop->GrowthDay);
                                    Emergence = 0;
                                    Crop->TSumEmergence = 0;
                                    Crop->Emergence = 0;
                                    Crop->Sowing    = 0;
                                }
                            }
                        }    

                        /* Store the daily calculations in the Grid structure */
                        Grid->crp  = Crop;
                        Grid->soil = WatBal;
                        Grid->mng  = Mng;
                        Grid->ste  = Site;
                        Grid = Grid->next;
                    }
                }
            }
        }
        
        head = Meteo;
        Meteo = Meteo->next;
        CleanMeteo(head);
        free(head);
    }
    
    /* Return to the beginning of the list */
    Grid = initial;
    
    /* Close the output files and free the allocated memory */
    while(Grid)
    {
        fclose(output[Grid->file]);
        Grid = Grid->next;
    }
    free(output);

    /* Go back to the beginning of the list */
    Grid = initial;
    Clean(Grid);

    return 1;
}
