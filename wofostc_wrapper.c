#include <stdio.h>
// Include methods for input/output channels
#include "YggInterface.h"

int main(int argc, char *argv[]) {
  // Initialize input/output channels
  yggInput_t in_channel = yggGenericInput("input");
  yggOutput_t out_channel = yggGenericOutput("output");

  // Declare resulting variables and create buffer for received message
  int flag = 1;
  generic_t obj = init_generic();  
  char** keys = NULL;
  size_t nkeys, i;

  // Cropfile variables
  double tbasem;
  double teffmx;
  double tsumem;
  double idsl;
  double dlo;
  double dlc;
  double tsum1;
  double tsum2;
  double* dtsmtb_x = NULL;
  double* dtsmtb_y = NULL;
  generic_t dtsmtb;
  size_t n_dtsmtb;
  double dvsi;
  double dvsend;
  double tdwi;
  double laiem;
  double rgrlai;
  double* slatb_x = NULL;
  double* slatb_y = NULL;
  generic_t slatb;
  size_t n_slatb;
  double spa;
  double* ssatb_x = NULL;
  double* ssatb_y = NULL;
  generic_t ssatb;
  size_t n_ssatb;
  double span;
  double tbase;
  double* kdiftb_x = NULL;
  double* kdiftb_y = NULL;
  generic_t kdiftb;
  size_t n_kdiftb;
  double* efftb_x = NULL;
  double* efftb_y = NULL;
  generic_t efftb;
  size_t n_efftb;
  double* amaxtb_x = NULL;
  double* amaxtb_y = NULL;
  generic_t amaxtb;
  size_t n_amaxtb;
  double* tmpftb_x = NULL;
  double* tmpftb_y = NULL;
  generic_t tmpftb;
  size_t n_tmpftb;
  double* tmnftb_x = NULL;
  double* tmnftb_y = NULL;
  generic_t tmnftb;
  size_t n_tmnftb;
  double co2;
  double* co2amaxtb_x = NULL;
  double* co2amaxtb_y = NULL;
  generic_t co2amaxtb;
  size_t n_co2amaxtb;
  double* co2efftb_x = NULL;
  double* co2efftb_y = NULL;
  generic_t co2efftb;
  size_t n_co2efftb;
  double* co2tratb_x = NULL;
  double* co2tratb_y = NULL;
  generic_t co2tratb;
  size_t n_co2tratb;
  double cvl;
  double cvo;
  double cvr;
  double cvs;
  double q10;
  double rml;
  double rmo;
  double rmr;
  double rms;
  double* rfsetb_x = NULL;
  double* rfsetb_y = NULL;
  generic_t rfsetb;
  size_t n_rfsetb;
  double* frtb_x = NULL;
  double* frtb_y = NULL;
  generic_t frtb;
  size_t n_frtb;
  double* fltb_x = NULL;
  double* fltb_y = NULL;
  generic_t fltb;
  size_t n_fltb;
  double* fstb_x = NULL;
  double* fstb_y = NULL;
  generic_t fstb;
  size_t n_fstb;
  double* fotb_x = NULL;
  double* fotb_y = NULL;
  generic_t fotb;
  size_t n_fotb;
  double perdl;
  double* rdrrtb_x = NULL;
  double* rdrrtb_y = NULL;
  generic_t rdrrtb;
  size_t n_rdrrtb;
  double* rdrstb_x = NULL;
  double* rdrstb_y = NULL;
  generic_t rdrstb;
  size_t n_rdrstb;
  double cfet;
  double depnr;
  double iairdu;
  double iox;
  double rdi;
  double rri;
  double rdmcr;
  double dvsdr;
  double dvsdlt;
  double rdrlv_npk;
  double dvs_npk_stop;
  double dvs_npk_transl;
  double npk_translrt_fr;
  double ncrit_fr;
  double pcrit_fr;
  double kcrit_fr;
  double nmaxrt_fr;
  double nmaxst_fr;
  double pmaxrt_fr;
  double pmaxst_fr;
  double kmaxrt_fr;
  double kmaxst_fr;
  double nlai_npk;
  double nlue_npk;
  double nmaxso;
  double pmaxso;
  double kmaxso;
  double npart;
  double nsla_npk;
  double nresidlv;
  double nresidst;
  double nresidrt;
  double presidlv;
  double presidst;
  double presidrt;
  double kresidlv;
  double kresidst;
  double kresidrt;
  double tcnt;
  double tcpt;
  double tckt;
  double nfix_fr;
  double* nmaxlv_tb_x = NULL;
  double* nmaxlv_tb_y = NULL;
  generic_t nmaxlv_tb;
  size_t n_nmaxlv_tb;
  double* pmaxlv_tb_x = NULL;
  double* pmaxlv_tb_y = NULL;
  generic_t pmaxlv_tb;
  size_t n_pmaxlv_tb;
  double* kmaxlv_tb_x = NULL;
  double* kmaxlv_tb_y = NULL;
  generic_t kmaxlv_tb;
  size_t n_kmaxlv_tb;
  
  // Soilfile variables
  double* smtab_x = NULL;
  double* smtab_y = NULL;
  generic_t smtab;
  size_t n_smtab;
  double smw;
  double smfcf;
  double sm0;
  double crairc;
  double* contab_x = NULL;
  double* contab_y = NULL;
  generic_t contab;
  size_t n_contab;
  double k0;
  double sope;
  double ksub;
  double spads;
  double spods;
  double spass;
  double sposs;
  double deflim;
  
  // Mgmtfile variables
  double* ferntab_x = NULL;
  double* ferntab_y = NULL;
  generic_t ferntab;
  size_t n_ferntab;
  double* ferptab_x = NULL;
  double* ferptab_y = NULL;
  generic_t ferptab;
  size_t n_ferptab;
  double* ferktab_x = NULL;
  double* ferktab_y = NULL;
  generic_t ferktab;
  size_t n_ferktab;
  double nrftab;
  double prftab;
  double krftab;
  double nmins;
  double rtnmins;
  double pmins;
  double rtpmins;
  double kmins;
  double rtkmins;
  double* irrtab_x = NULL;
  double* irrtab_y = NULL;
  generic_t irrtab;
  size_t n_irrtab;
  
  // Sitefile variables
  double izt;
  double ifunrn;
  double idrain;
  double ssmax;
  double wav;
  double zti;
  double dd;
  double rdmsol;
  double notinf;
  double ssi;
  double smlim;
  double* ninftb_x = NULL;
  double* ninftb_y = NULL;
  generic_t ninftb;
  size_t n_ninftb;
  
  // Initialization variables
  double start_date;
  double emergence;
  double start_year;
  double end_year;

  // Loop until there is no longer input or the queues are closed
  while (flag >= 0) {
  
    // Receive input from input channel
    // If there is an error, the flag will be negative
    // Otherwise, it is the size of the received message
    flag = yggRecv(in_channel, &obj);
    if (flag < 0) {
      printf("C Model: No more input.\n");
      break;
    }

    // Print received message
    printf("C Model:\n");
    display_generic(obj);

    // Print keys
    nkeys = generic_map_get_keys(obj, &keys);
    printf("C Model: keys = ");
    for (i = 0; i < nkeys; i++) {
      printf("%s ", keys[i]);
    }
    printf("\n");

    // Get double precision floating point elements
    tbasem = generic_map_get_double(obj, "TBASEM");
    printf("C Model: TBASEM = %lf\n", tbasem);
	
	teffmx = generic_map_get_double(obj, "TEFFMX");
    printf("C Model: TEFFMX = %lf\n", teffmx);

    // Get array elements
	amaxtb = generic_map_get_array(obj, "AMAXTB");
    n_amaxtb = generic_array_get_1darray_double(amaxtb, 0, &amaxtb_x);
    generic_array_get_1darray_double(amaxtb, 1, &amaxtb_y);
    printf("C Model: AMAXTB = \n");
    for (i = 0; i < n_amaxtb; i++) {
      printf("\t%lf\t%lf\n", amaxtb_x[i], amaxtb_y[i]);
    }

    // Send output to output channel
    // If there is an error, the flag will be negative
    flag = yggSend(out_channel, obj);
    if (flag < 0) {
      printf("C Model: Error sending output.\n");
      break;
    }

    // Free dynamically allocated variables for this loop
    free_generic(&amaxtb);

  }

  // Free dynamically allocated obj structure
  free_generic(&obj);
  free(amaxtb_x);
  free(amaxtb_y);
  free(keys);
  
  return 0;
}