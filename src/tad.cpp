/* Prueba:
     InsCabeza, InsertarI, InsertarD
*/
#include <iostream>

using namespace std;

#include "tlistacom.h"

int
main(void)
{
  TComplejo a, b(1), c(2, 3);
  TListaCom l1;
  
  cout<<"l1 = "<<l1<<endl;
  l1.InsCabeza(a);
  cout<<"l1 = "<<l1<<endl;
  l1.InsertarI(b, l1.Ultima());
  cout<<"l1 = "<<l1<<endl;
  l1.InsertarD(c, l1.Primera());

  cout<<"l1 = "<<l1<<endl;
   
  return 0;
}
