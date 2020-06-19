///1+1 dimensional scalar field monte-carlo calculation
///Everything about this code is bad - on purpose

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int idx(int i, int j, int NX, int NT)
{
  return ((i+NX) % NX)*NT + ((j+NT) % NT);
}

double total_action(double phi[], int m, int NX, int NT)
{
  double total = 0.;
  for(int i=0; i<NX; ++i)
  for(int j=0; j<NT; ++j)
  {
    ///u=0
    total += phi[idx(i,j,NX,NT)]*phi[idx(i+1,j,NX,NT)];
    total += phi[idx(i,j,NX,NT)]*phi[idx(i-1,j,NX,NT)];
    ///u=1
    total += phi[idx(i,j,NX,NT)]*phi[idx(i,j+1,NX,NT)];
    total += phi[idx(i,j,NX,NT)]*phi[idx(i,j-1,NX,NT)];

    ///mass term
    total += (4 + m*m)*phi[idx(i,j,NX,NT)]*phi[idx(i,j,NX,NT)];
  }

  return 0.5*total;
}


void print_field(double phi[], int NX, int NT)
{
  for(int i=0; i<NX; ++i)
  {
    for(int j=0; j<NT; ++j)
    {
      printf("%f ", phi[idx(i,j,NX,NT)]);
    }
    printf("\n");
  }
}

double delta_s(double phi[], double phi_prime, double m, int i, int j, int NX, int NT)
{
  double deriv_part_nm = (phi[idx(i,j,NX,NT)]-phi_prime)*(phi[idx(i+1,j,NX,NT)] + phi[idx(i-1,j,NX,NT)] 
                                                      +phi[idx(i,j+1,NX,NT)] + phi[idx(i,j-1,NX,NT)]);

  double deriv_part_other = (phi[idx(i+1,j,NX,NT)] + phi[idx(i-1,j,NX,NT)]
                            +phi[idx(i,j+1,NX,NT)] + phi[idx(i,j-1,NX,NT)])*(phi[idx(i,j,NX,NT)]-phi_prime);

  double mass_part = (4. + m)*(phi[idx(i,j,NX,NT)]*phi[idx(i,j,NX,NT)] - phi_prime*phi_prime);

  return 0.5*(deriv_part_nm + deriv_part_other + mass_part);
}


int main()
{
  int NX = 128;
  int NT = 128;
  int NC = 500;
  int m = 1;
  
  double phi[NX*NT];

/*  
  printf("Checking indexing...\n");
  for(int i=-1; i<=NX; ++i)
  {
    for(int j=-1; j<=NT; ++j)
    {
      printf("idx(%d,%d)=%d  ",i,j,idx(i,j,NX,NT));
    }
    printf("\n");
  }
*/

  ///Cold Start
  for(int i=0; i<NX; ++i)
  for(int j=0; j<NT; ++j)
  {
    phi[idx(i,j,NX,NT)] = 1.0;
  }
  printf("The field for a cold start is...\n");
  print_field(phi, NX, NT);  
  double original_action = total_action(phi,m,NX,NT);
  printf("Action of cold start field = %f\n", original_action);

  printf("\nChecking that the delta_s function works\n");
  phi[idx(1,1,NX,NT)] = 0.5;
  printf("Difference in total action = %f\n", original_action - total_action(phi, m, NX, NT));
  phi[idx(1,1,NX,NT)] = 1.0;
  printf("Result of delta_s function = %f\n", delta_s(phi, 0.5, m, 1, 1, NX, NT));

//  int measurements = (NC-100)/5;
//  double avg_phi[measurements], action[measurements];
  FILE *phi_file = fopen("phi_measurements.txt", "w");
  FILE *s_file = fopen("action_measurements.txt", "w");
  
  for(int c=0; c<NC; ++c)
  {
    ///for each lattice site
    for(int i=0; i<NX; ++i)
    for(int j=0; j<NT; ++j)
    {
      ///pick a random test field from -1 to 1
      double phi_prime = (rand()/(double)(RAND_MAX))*2 - 1;
      ///compute delta S
      double del_s = delta_s(phi, phi_prime, m, i, j, NX, NT);
      double compare_num = (rand()/(double)(RAND_MAX)); 
 //     printf("Report on update attempt:  phi=%f, phi_prime=%f, del_s=%f\n", phi[idx(i,j,NX,NT)], phi_prime, del_s); 
      ///accept/reject
      if( compare_num < exp(del_s) )
      {
//        double orig_action = total_action(phi, m, NX, NT);
        phi[idx(i,j,NX,NT)] = phi_prime;
 //       printf("del_s = %f  |  total_action_diff = %f\n", del_s, orig_action - total_action(phi, m, NX, NT));
      }
    } 
    double avg_phi = 0.;
    for(int i=0; i<NX; ++i)
    for(int j=0; j<NT; ++j)
    {
      avg_phi += phi[idx(i,j,NX,NT)];
    }
    fprintf(phi_file,"%d %f\n",c,avg_phi/((double)(NX*NT)));     
    fprintf(s_file,"%d %f\n",c,total_action(phi, m, NX, NT));     
  }


  return 0;
}
