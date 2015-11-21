#include <unistd.h>
#include <getopt.h>
#include "global.h"
#include "trace_line.h"
#include "tracer.h"
#include "trace_ids.h"

void print_help(){
		printf("\nOptions :\n\n-F <flow_id>/'all' : traces the given \
flow id or, if the option 'all' is used, traces the NUMBER of different \
flows\n-f : the name of the file to parse\n-h : get help! \
\n-r <router_id>/'all' : traces the given \
router or, if the option 'all' is used, traces the NUMBER of total packets \
transiting through each router.\n\n");
			 }



int main (int argc, char* argv[]) {

	clock_t begin, end;
	double time_spent;
	int trace_routers = -1;
	char * file_name = NULL;
	int flow_value = 0;
	int c;
	
	opterr = 0;

	while ((c = getopt (argc, argv, "F:f:hsr:")) != -1)
    switch (c)
      {
	  /*F : number of flows*/	  
      case 'F':
	if(strcmp(optarg,"all") == 0){
        flow_value = -1;
	}else{	
        flow_value = atoi(optarg);
	}
        break;
       case 'f':
        printf("filename : %s\n",optarg);
        file_name = optarg;
        break;
        case 'r':
        if(strcmp(optarg,"all") == 0){
        flow_value = 0;
		}else{	
			trace_routers = atoi(optarg);
		}
        break;
      /*h : print help*/
      case 'h':
        print_help();
        return 0;
        break;
      /*CASE OF ARGUMENT VALUES  
      case 'c':
        cvalue = optarg;
        break;*/
      case '?':
        if (optopt == 'c')
          fprintf (stderr, "Option -%c requires an argument.\n", 
          optopt);
        else if (isprint (optopt))
          fprintf (stderr, "Unknown option `-%c'.\n", optopt);
        else
          fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        printf("For help : type ./read -h\n");
        return 1;
      default:
        abort ();
      }

	
	begin = clock();
	read_file(file_name,flow_value,trace_routers);
	
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	time_spent = truncate(time_spent);
	printf("Time spent : %0.1f second(s)\n",time_spent);

	
        return 0; 
}
