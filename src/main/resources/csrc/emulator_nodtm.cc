#include "verilated.h"
#include "verilated_vcd_c.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
// bool verbose;
// bool done_reset;

int main(int argc, char *argv[]) {
  uint64_t max_cycles = -1;
  int opt;
  FILE * vcdfile = NULL;

  while ((opt = getopt(argc, argv, "m:v:")) != -1) {
    switch (opt) {
      case 'm': max_cycles = atoll(optarg); break;
#if VM_TRACE
      case 'v': {
        vcdfile = strcmp(optarg, "-") == 0 ? stdout : fopen(optarg, "w");
        if (!vcdfile) {
          std::cerr << "Unable to open " << optarg << " for VCD write\n";
          return 1;
        }
        break;
      }
#endif
      default: goto simulation;
      
    }
  }

  simulation:
    Verilated::commandArgs(argc, argv);
    TEST_HARNESS *tile = new TEST_HARNESS;
    #if VM_TRACE
      printf("VM_TRACE is def");
      if( vcdfile == NULL ) {
          // Error, as expected.
          perror( "Error opening file" );
          printf( "Error code opening file: %d\n", errno );
          printf( "Error opening file: %s\n", strerror( errno ) );
          exit(-1);
    }
      Verilated::traceEverOn(true); // Verilator must compute traced signals$
      std::unique_ptr<VerilatedVcdFILE> vcdfd(new VerilatedVcdFILE(vcdfile));
      std::unique_ptr<VerilatedVcdC> tfp(new VerilatedVcdC(vcdfd.get()));
      if(vcdfile){
        tile->trace(tfp.get(), 99);  // Trace 99 levels of hierarchy
        tfp->open("");
      }
    #endif  
    int current_cycle = 0;
    auto tick = [tile]() {
      tile->clock = !tile->clock;
      tile->eval();
      tile->clock = !tile->clock;
      tile->eval();
    };
    

      
    tile->reset = 1;
    for (int i = 0; i < 10; i++) tick();
    tile->reset = 0;
    tick();
    int x = 0;
    while(!Verilated::gotFinish()){
      tick();
      current_cycle = current_cycle+1;
      #if VM_TRACE
        tfp->dump(static_cast<vluint64_t>(x));
        x=x+1;
      #endif
      if(max_cycles == current_cycle) {
        fprintf(stderr, "*** FAILED *** via trace_count (timeout) after %d cycles\n", current_cycle);
        exit(0);
      }
    }

    #if VM_TRACE
      if(tfp){
        tfp->close();
      }
      if (vcdfile)
        fclose(vcdfile);
    #endif
}