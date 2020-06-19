///1+1 dimensional scalar field monte-carlo calculation

#include <stdio.h>

int idx(int i, int j, int NX, int NT)
{
  return (i % NX)*NT + (j % NT);
}

double total_action(double phi[], int m, int NX, int NT)
{
  double total = 0.;
  for(int i=0; i<NX; ++i)
  for(int j=0; j<NT; ++j)
  {
    ///u=0
    total += phi[idx(i,j,NX,NT)]*phi[idx(i+1,j,NX,NT)];
    ///u=1
    total += phi[idx(i,j,NX,NT)]*phi[idx(i,j+1,NX,NT)];

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

int main()
{
  int NX = 4;
  int NT = 4;
  int NC = 100;
  int m = 1;
  
  double phi[NX*NT];
  
  ///Cold Start
  for(int i=0; i<NX; ++i)
  for(int j=0; j<NT; ++j)
  {
    phi[idx(i,j,NX,NT)] = 1.0;
  }
  printf("The field is...\n");
  print_field(phi, NX, NT);  
  printf("Action of cold start field = %f\n", total_action(phi,m,NX,NT));

  return 0;
}
