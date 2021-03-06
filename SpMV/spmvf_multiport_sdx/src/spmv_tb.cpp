#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "spmv.h"
#include "time.h"

#include "sds_lib.h"

#include <sys/time.h>

double getTimestamp() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_usec + tv.tv_sec*1e6;
}


double hardware_start;
double hardware_end;
double hardware_execution_time;

double software_start;
double software_end;
double software_execution_time;


void SpMV_Ref(char* inputFile, DATA_TYPE *y) {

	FILE *fp;


	int r;
	int c;
	DATA_TYPE v;

	unsigned long int row_size = 0;
	unsigned long int col_size = 0;
	unsigned long int data_size = 0;

	DATA_TYPE *x;
	u32       *rows;
	DATA_TYPE *values;
	u32       *cols;

	fp = fopen(inputFile, "r");


	if (fp != NULL) {
	   char line [1000];
	   while(fgets(line,sizeof line,fp)!= NULL) {// read a line from a file
		   if (line[0] != '%') {

			   sscanf( line, "%lu %lu %lu", &row_size, &col_size, &data_size);


			   x        = (DATA_TYPE*)malloc(col_size*sizeof(DATA_TYPE));
			   rows     = (u32*)malloc(row_size*sizeof(u32));
			   values   = (DATA_TYPE*)malloc(data_size*sizeof(DATA_TYPE));
			   cols     = (u32*)malloc(data_size*sizeof(u32));

			   for (unsigned int i = 0; i < (row_size); i++) {
				   if(fgets(line,sizeof line,fp)!= NULL) {
					   sscanf( line, "%d ", &r);
					   rows[i] = r;
				   } else {
					   printf("error reading file 1\n");
				   }
			   }
			   for (unsigned int i = 0; i < data_size; i++) {
				   if(fgets(line,sizeof line,fp)!= NULL) {
					   sscanf( line, "%d %f", &c, &v);
					   if (v == 0) {
//						   printf("col = %d val=%f\n", c, v);
					   }
					   cols[i] = c;
					   values[i] = v;
				   } else {
					   printf("error reading file 1\n");
				   }
			   }
			   break;
		   }
	   }
	   fclose(fp);
	} else {
		perror(inputFile); //print the error message on stderr.
	}


	for (unsigned int i = 0; i < col_size; i++) {
		x[i] = i;//(1.0*rand()+1.0)/RAND_MAX;
	}

    int i=0, j=0, rowStart=0, rowEnd=row_size;

    DATA_TYPE y0=0.0;
    int last_j = 0;
    for (i = rowStart; i < rowEnd; ++i) {
    	y0 = 0.0;
    	int new_index_j = last_j+rows[i];
        for (j = last_j ; j < new_index_j; ++j) {
        	y0 += values[j] * x[cols[j]];
        }
        last_j = last_j + rows[i];
        y[i] = y0;
    }


    free(x);
	free(rows);
	free(values);
	free(cols);
}


void spmv_init( uintbuswidth_t **values_indices_1,
				uintbuswidth_t **values_indices_2,
				uintbuswidth_t **values_indices_3,
				uintbuswidth_t **values_indices_4,


				uintbuswidth_t **x,

				u32 *rows_1_size,
				u32 *rows_2_size,
				u32 *rows_3_size,
				u32 *rows_4_size,
				u32 *rows_5_size,
				u32 *rows_6_size,
				u32 *rows_7_size,
				u32 *rows_8_size,
				u32 *row_size_max,

				u32 *values_1_size,
				u32 *values_2_size,
				u32 *values_3_size,
				u32 *values_4_size,
				u32 *values_5_size,
				u32 *values_6_size,
				u32 *values_7_size,
				u32 *values_8_size,


				u32  *col_size,
				u32  *compact_indices_size,
				char* inputFile) {

	FILE *fp;






	   unsigned long int c, r1, r2,r3, r4,r5, r6,r7, r8, v1, v2, v3, v4, v5, v6, v7, v8;


	fp = fopen(inputFile, "r");

	if (fp != NULL) {
	   char line [1000];
	   while(fgets(line,sizeof line,fp)!= NULL) {// read a line from a file
		   if (line[0] != '%') {
			   sscanf( line, "%lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu", &c, &r1, &r2,&r3, &r4,&r5, &r6,&r7, &r8, &v1, &v2, &v3, &v4, &v5, &v6, &v7, &v8);
					   *col_size = c;
					   *rows_1_size = r1;
					   *rows_2_size = r2;
					   *rows_3_size = r3;
					   *rows_4_size = r4;
					   *rows_5_size = r5;
					   *rows_6_size = r6;
					   *rows_7_size = r7;
					   *rows_8_size = r8;
					   *values_1_size = v1;
					   *values_2_size = v2;
					   *values_3_size = v3;
					   *values_4_size = v4;
					   *values_5_size = v5;
					   *values_6_size = v6;
					   *values_7_size = v7;
					   *values_8_size = v8;




			   *row_size_max = *rows_1_size;
			   if (*row_size_max < *rows_2_size)
				   *row_size_max = *rows_2_size;
			   if (*row_size_max < *rows_3_size)
				   *row_size_max = *rows_3_size;
			   if (*row_size_max < *rows_4_size)
				   *row_size_max = *rows_4_size;
			   if (*row_size_max < *rows_5_size)
				   *row_size_max = *rows_5_size;
			   if (*row_size_max < *rows_6_size)
				   *row_size_max = *rows_6_size;
			   if (*row_size_max < *rows_7_size)
				   *row_size_max = *rows_7_size;
			   if (*row_size_max < *rows_8_size)
				   *row_size_max = *rows_8_size;



			   u32 values_size_max = *values_1_size;
			   if (values_size_max < *values_2_size)
				   values_size_max = *values_2_size;
			   if (values_size_max < *values_3_size)
				   values_size_max = *values_3_size;
			   if (values_size_max < *values_4_size)
				   values_size_max = *values_4_size;
			   if (values_size_max < *values_5_size)
				   values_size_max = *values_5_size;
			   if (values_size_max < *values_6_size)
				   values_size_max = *values_6_size;
			   if (values_size_max < *values_7_size)
				   values_size_max = *values_7_size;
			   if (values_size_max < *values_8_size)
				   values_size_max = *values_8_size;


			   u32 indices_size = *rows_1_size + *values_1_size;
			   if (indices_size < *rows_2_size + *values_2_size)
				   indices_size = *rows_2_size + *values_2_size;
			   if (indices_size < *rows_3_size + *values_3_size)
				   indices_size = *rows_3_size + *values_3_size;
			   if (indices_size < *rows_4_size + *values_4_size)
				   indices_size = *rows_4_size + *values_4_size;
			   if (indices_size < *rows_5_size + *values_5_size)
				   indices_size = *rows_5_size + *values_5_size;
			   if (indices_size < *rows_6_size + *values_6_size)
				   indices_size = *rows_6_size + *values_6_size;
			   if (indices_size < *rows_7_size + *values_7_size)
				   indices_size = *rows_7_size + *values_7_size;
			   if (indices_size < *rows_8_size + *values_8_size)
				   indices_size = *rows_8_size + *values_8_size;




			   *compact_indices_size = indices_size;
			   *x        = (uintbuswidth_t*)sds_alloc_non_cacheable(*col_size*sizeof(uintbuswidth_t));

			   *values_indices_1 = (uintbuswidth_t*)sds_alloc_non_cacheable(*compact_indices_size *sizeof(uintbuswidth_t));
			   *values_indices_2 = (uintbuswidth_t*)sds_alloc_non_cacheable(*compact_indices_size *sizeof(uintbuswidth_t));
			   *values_indices_3 = (uintbuswidth_t*)sds_alloc_non_cacheable(*compact_indices_size *sizeof(uintbuswidth_t));
			   *values_indices_4 = (uintbuswidth_t*)sds_alloc_non_cacheable(*compact_indices_size *sizeof(uintbuswidth_t));

			   for(unsigned int i = 0; i < *compact_indices_size; i++) {
				   (*values_indices_1)[i] = 0;
				   (*values_indices_2)[i] = 0;
				   (*values_indices_3)[i] = 0;
				   (*values_indices_4)[i] = 0;
			   }

			   unsigned long int index_1, index_2, index_3, index_4, index_5, index_6, index_7, index_8;
			   for (unsigned int i = 0; i < indices_size; i++) {
				   fgets(line,sizeof line,fp);
				   sscanf( line, "%lu %lu %lu %lu %lu %lu %lu %lu", &index_1, &index_2, &index_3, &index_4, &index_5, &index_6, &index_7, &index_8);


				   (*values_indices_1)[i].range(31,  0)   = index_1;
				   (*values_indices_1)[i].range(95,  64)  = index_2;

				   (*values_indices_2)[i].range(31,  0)   = index_3;
				   (*values_indices_2)[i].range(95,  64)  = index_4;

				   (*values_indices_3)[i].range(31,  0)   = index_5;
				   (*values_indices_3)[i].range(95,  64)  = index_6;

				   (*values_indices_4)[i].range(31,  0)   = index_7;
				   (*values_indices_4)[i].range(95,  64)  = index_8;
			   }

			   u32 value_index = 0;
			   DATA_TYPE value_1, value_2, value_3, value_4, value_5, value_6, value_7, value_8;
			   for (unsigned int i = 0; i < indices_size; i++) {
				   fgets(line,sizeof line,fp);
				   sscanf( line, "%f %f %f %f %f %f %f %f ", &value_1, &value_2, &value_3, &value_4, &value_5, &value_6, &value_7, &value_8);
				   union float_ap_uint32_t tmp;

				   tmp.f = value_1;
				   (*values_indices_1)[value_index].range(63,  32)   = tmp.apint;
				   tmp.f = value_2;
				   (*values_indices_1)[value_index].range(127,  96)   = tmp.apint;

				   tmp.f = value_3;
				   (*values_indices_2)[value_index].range(63,  32)   = tmp.apint;
				   tmp.f = value_4;
				   (*values_indices_2)[value_index].range(127,  96)   = tmp.apint;

				   tmp.f = value_5;
				   (*values_indices_3)[value_index].range(63,  32)   = tmp.apint;
				   tmp.f = value_6;
				   (*values_indices_3)[value_index].range(127,  96)   = tmp.apint;

				   tmp.f = value_7;
				   (*values_indices_4)[value_index].range(63,  32)   = tmp.apint;
				   tmp.f = value_8;
				   (*values_indices_4)[value_index].range(127,  96)   = tmp.apint;




				   value_index++;
			   }

/*				*rows_1_size =
;
				*rows_2_size = row_size_max;
				*rows_3_size = row_size_max;
				*rows_4_size = row_size_max;
				*rows_5_size = row_size_max;
				*rows_6_size = row_size_max;
				*rows_7_size = row_size_max;
				*rows_8_size = row_size_max;


				*values_1_size = values_size_max;
				*values_2_size = values_size_max;
				*values_3_size = values_size_max;
				*values_4_size = values_size_max;
				*values_5_size = values_size_max;
				*values_6_size = values_size_max;
				*values_7_size = values_size_max;
				*values_8_size = values_size_max;
*/
			   break;
		   }
	   }

	   fclose(fp);
	 }
	 else {
	    perror(inputFile); //print the error message on stderr.
	 }






    for (unsigned int i = 0; i < *col_size; i++) {
    	(*x)[i].range(31, 0) = i;//(1.0*rand()+1.0)/RAND_MAX;
    }


}

int main(int argc, char **argv) {

	int status                   = 0;


	//DATA_TYPE *y_hw              = NULL;

	DATA_TYPE *y_sw              = NULL;

	//uintbuswidth_t *y_hw_128bit       = NULL;






	uintbuswidth_t *x            = NULL;
	uintbuswidth_t *values_1     = NULL;
	uintbuswidth_t *values_2     = NULL;
	uintbuswidth_t *values_3     = NULL;
	uintbuswidth_t *values_4     = NULL;

	u32        values_1_size;
	u32        values_2_size;
	u32        values_3_size;
	u32        values_4_size;
	u32        values_5_size;
	u32        values_6_size;
	u32        values_7_size;
	u32        values_8_size;




	u32        rows_1_size;
	u32        rows_2_size;
	u32        rows_3_size;
	u32        rows_4_size;
	u32        rows_5_size;
	u32        rows_6_size;
	u32        rows_7_size;
	u32        rows_8_size;
	u32        row_size_max;
	u32        compact_indices_size;


	u32        row_size, col_size;





	char II_string[10];//="8";

	sprintf(II_string, "%d", II);


	char* inputFile_name;
	char inputFile[1000]= "";
	char fpgaFileName[1000]= "";
	char goldenFileName[1000]= "";

	strcpy(inputFile, argv[2]);

	int no_iterations = atoi(argv[1]);


	char* ts1 = strdup(inputFile);
	char* ts2 = strdup(inputFile);

	char* dir = dirname(ts1);
	inputFile_name = basename(ts2);

	if(strstr(inputFile_name, ".mtx") != NULL) {
		printf("please remove the file extension");
		exit(1);
	}

	printf("dir=%s, filename=%s, \n", dir, inputFile_name);


	strcpy(fpgaFileName, dir);
	strcat(fpgaFileName, "/");
	strcat(fpgaFileName, "partitioned_8_II=");
	strcat(fpgaFileName, II_string);
	strcat(fpgaFileName, inputFile_name);
	strcat(fpgaFileName, ".mtx");


	strcpy(goldenFileName, dir);
	strcat(goldenFileName, "/");
	strcat(goldenFileName, "fpga_csr_");
	strcat(goldenFileName, inputFile_name);
	strcat(goldenFileName, ".mtx");





	spmv_init(
			&values_1,
			&values_2,
			&values_3,
			&values_4,


		    &x,

			&rows_1_size,
			&rows_2_size,
			&rows_3_size,
			&rows_4_size,
			&rows_5_size,
			&rows_6_size,
			&rows_7_size,
			&rows_8_size,
			&row_size_max,

			&values_1_size,
			&values_2_size,
			&values_3_size,
			&values_4_size,
			&values_5_size,
			&values_6_size,
			&values_7_size,
			&values_8_size,

			&col_size,

			&compact_indices_size,
			fpgaFileName);

	row_size = rows_1_size + rows_2_size + rows_3_size + rows_4_size + rows_5_size + rows_6_size + rows_7_size + rows_8_size;
	y_sw         = (DATA_TYPE*)malloc(row_size*sizeof(DATA_TYPE));


	union float_uint128 {
		uintbuswidth_t *y_hw_128bit;
		DATA_TYPE      *y_hw;
	};

	union float_uint128 y_union;
	y_union.y_hw_128bit = (uintbuswidth_t*)sds_alloc_non_cacheable((row_size/4+1)*sizeof(uintbuswidth_t));




	printf("\rHello MM!\n\r");




	SpMV_Ref(goldenFileName, y_sw);

	printf("\rHardware version started!\n\r");
	hardware_start = getTimestamp();


	spmv_accel(
			values_1,
			values_2,
			values_3,
			values_4,


			compact_indices_size,

			x,

			y_union.y_hw_128bit,


			rows_1_size,
			rows_2_size,
			rows_3_size,
			rows_4_size,
			rows_5_size,
			rows_6_size,
			rows_7_size,
			rows_8_size,
			row_size_max,

			values_1_size,
			values_2_size,
			values_3_size,
			values_4_size,
			values_5_size,
			values_6_size,
			values_7_size,
			values_8_size,

			col_size,
			compact_indices_size);

    hardware_end = getTimestamp();



	hardware_execution_time = (hardware_end-hardware_start)/(1000);
	printf("first time hardware execution time  %.6f ms elapsed\n", hardware_execution_time);


	printf("\rHardware version started!\n\r");
	hardware_start = getTimestamp();


	spmv_accel(
			values_1,
			values_2,
			values_3,
			values_4,


			compact_indices_size,

			x,

			y_union.y_hw_128bit,


			rows_1_size,
			rows_2_size,
			rows_3_size,
			rows_4_size,
			rows_5_size,
			rows_6_size,
			rows_7_size,
			rows_8_size,
			row_size_max,

			values_1_size,
			values_2_size,
			values_3_size,
			values_4_size,
			values_5_size,
			values_6_size,
			values_7_size,
			values_8_size,

			col_size,
			compact_indices_size);

    hardware_end = getTimestamp();



	hardware_execution_time = (hardware_end-hardware_start)/(1000);
	printf("second time hardware execution time  %.6f ms elapsed\n", hardware_execution_time);


	printf("\rHardware version started!\n\r");
	hardware_start = getTimestamp();

	for (int i = 0; i < no_iterations; i++) {
		spmv_accel(
				values_1,
				values_2,
				values_3,
				values_4,


				compact_indices_size,

				x,

				y_union.y_hw_128bit,


				rows_1_size,
				rows_2_size,
				rows_3_size,
				rows_4_size,
				rows_5_size,
				rows_6_size,
				rows_7_size,
				rows_8_size,
				row_size_max,

				values_1_size,
				values_2_size,
				values_3_size,
				values_4_size,
				values_5_size,
				values_6_size,
				values_7_size,
				values_8_size,

				col_size,
				compact_indices_size);
	}
    hardware_end = getTimestamp();



	hardware_execution_time = (hardware_end-hardware_start)/(1000*no_iterations);
	printf("average time hardware execution time  %.6f ms elapsed\n", hardware_execution_time);


	for(unsigned int i=0;i<row_size;i++) {
		DATA_TYPE diff = fabs(y_sw[i]-y_union.y_hw[i]);
		if(diff > 0.1 || diff != diff){
			printf("error occurs at  %d with value y_hw = %f, should be y_sw = %f \n",i,y_union.y_hw[i],y_sw[i]);
			status = -1;
			break;
	    }


	}
	if(!status) {
		printf("Validation PASSED!\n");
	} else {
		printf("Validation FAILED!\n");
	}


    sds_free(x);
    sds_free(values_1);
    sds_free(values_2);
    sds_free(values_3);
    sds_free(values_4);
    sds_free(y_union.y_hw_128bit);




//    free(y_hw);
    free(y_sw);

	printf("\rBye mm!\n\r");

    return 0;
}


