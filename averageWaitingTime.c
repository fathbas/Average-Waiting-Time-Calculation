#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct process{
	char name[76];
	int e;
	int eLast;
	int time;
	float priority;
	int waitTime;
}process;


  #include "fatal.h"
	    
        #define Infinity (6000000000L)

		
		#define MaxTrees (12)   
        #define Capacity (4095)

        struct BinNode;
        typedef struct BinNode *BinTree;
        struct Collection;
        typedef struct Collection *BinQueue;

        BinQueue Initialize( void );
        void Destroy( BinQueue H );
        BinQueue Insert(process Item, BinQueue H );
        process DeleteMin( BinQueue H );
        BinQueue Merge( BinQueue H1, BinQueue H2 );
        process FindMin( BinQueue H );
        int IsEmpty( BinQueue H );
        int IsFull( BinQueue H );

        typedef struct BinNode *Position;

        struct BinNode
        {
		    struct process Item;
            Position    LeftChild;
            Position    NextSibling;
        };

        struct Collection
        {
            int CurrentSize;
            BinTree TheTrees[ MaxTrees ];
        };

        BinQueue
        Initialize( void )
        {
            BinQueue H;
            int i;

            H = malloc( sizeof( struct Collection ) );
            if( H == NULL )
                FatalError( "Out of space!!!" );
            H->CurrentSize = 0;
            for( i = 0; i < MaxTrees; i++ )
                H->TheTrees[ i ] = NULL;
            return H;
        }

        static void
        DestroyTree( BinTree T )
        {
            if( T != NULL )
            {
                DestroyTree( T->LeftChild );
                DestroyTree( T->NextSibling );
                free( T );
            }
        }

        void
        Destroy( BinQueue H )
        {
            int i;

            for( i = 0; i < MaxTrees; i++ )
                DestroyTree( H->TheTrees[ i ] );
        }

        BinQueue
        Insert( process Item, BinQueue H )
        {
            BinTree NewNode;
            BinQueue OneItem;
			

            NewNode = malloc( sizeof( struct BinNode ) );
            if( NewNode == NULL )
                FatalError( "Out of space!!!" );
            NewNode->LeftChild = NewNode->NextSibling = NULL;
			NewNode->Item = Item;
           

            OneItem = Initialize( );
            OneItem->CurrentSize = 1;
            OneItem->TheTrees[ 0 ] = NewNode;

            return Merge( H, OneItem );
        }

       

        process
        FindMin( BinQueue H)
        {
            int i;
            process MinItem;

            if( IsEmpty( H ) )
            {
               // Error( "Empty binomial queue" );
                return MinItem;
            }

            MinItem.priority = Infinity;
			
            for( i = 0; i < MaxTrees; i++ )
            {
                if( H->TheTrees[ i ] && H->TheTrees[ i ]->Item.priority <= MinItem.priority && H->TheTrees[ i ]->Item.e>0 ) {
                    MinItem = H->TheTrees[ i ]->Item;
				}	
            }

            return MinItem;
        }

        int
        IsEmpty( BinQueue H )
        {
            return H->CurrentSize == 0;
        }

        BinTree
        CombineTrees( BinTree T1, BinTree T2 )
        {
            if( T1->Item.priority > T2->Item.priority )
                return CombineTrees( T2, T1 );
            T2->NextSibling = T1->LeftChild;
            T1->LeftChild = T2;
            return T1;
        }

        BinQueue
        Merge( BinQueue H1, BinQueue H2 )
        {
            BinTree T1, T2, Carry = NULL;
            int i, j;

            if( H1->CurrentSize + H2->CurrentSize > Capacity )
                Error( "Merge would exceed capacity" );

            H1->CurrentSize += H2->CurrentSize;
            for( i = 0, j = 1; j <= H1->CurrentSize; i++, j *= 2 )
            {
                T1 = H1->TheTrees[ i ]; T2 = H2->TheTrees[ i ];

                switch( !!T1 + 2 * !!T2 + 4 * !!Carry )
                {
                    case 0: /* No trees */
                    case 1: /* Only H1 */
                        break;
                    case 2: /* Only H2 */
                        H1->TheTrees[ i ] = T2;
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 4: /* Only Carry */
                        H1->TheTrees[ i ] = Carry;
                        Carry = NULL;
                        break;
                    case 3: /* H1 and H2 */
                        Carry = CombineTrees( T1, T2 );
                        H1->TheTrees[ i ] = H2->TheTrees[ i ] = NULL;
                        break;
                    case 5: /* H1 and Carry */
                        Carry = CombineTrees( T1, Carry );
                        H1->TheTrees[ i ] = NULL;
                        break;
                    case 6: /* H2 and Carry */
                        Carry = CombineTrees( T2, Carry );
                        H2->TheTrees[ i ] = NULL;
                        break;
                    case 7: /* All three */
                        H1->TheTrees[ i ] = Carry;
                        Carry = CombineTrees( T1, T2 );
                        H2->TheTrees[ i ] = NULL;
                        break;
                }
            }
            return H1;
        }
		

int main()
{
float sumOfWaitTime = 0;
int eMax=0;
int totalTime=0;
int count=0;
char a[56];
int b;
int c;
BinQueue H1, H2;
BinTree p, r[20]={NULL};
process Item;

FILE *file;
file = fopen("input.txt", "r");	
if(file!=NULL){
while(fscanf(file,"%s %d %d",a,&b,&c)!=EOF){
 count++;
}	
}
fclose(file);

process *proList = (process*)malloc(sizeof(process)*count);
int i = 0;
FILE *file2;
file2 = fopen("input.txt", "r");	
if(file2!=NULL){
while(fscanf(file2,"%s %d %d",proList[i].name,&proList[i].e,&proList[i].time)!=EOF){
	proList[i].priority=0;
	proList[i].waitTime=0;
	proList[i].eLast=proList[i].e;
	if(proList[i].e>eMax){
		eMax=proList[i].e;
	}
	totalTime+=proList[i].e;
	i++;
}	
}
	fclose(file2);

process *proList2 = (process*)malloc(sizeof(process)*count);

for(int v=0; v<count; v++){
	proList2[v]=proList[v];
}

for(int q=1; q<=10; q++){
for(int v=0; v<count; v++){
	proList[v]=proList2[v];
}
sumOfWaitTime=0;
int i=0;
	while(i<=totalTime){
		 H1 = Initialize();
		for(int j=0; j<count; j++){
			if(proList[j].time<=i && proList[j].e>0){
				//priority hesaplacak 
				if(proList[j].e==proList[j].eLast){
					proList[j].priority=proList[j].e*1;
				}
				else{
					proList[j].priority=proList[j].e*(1/(exp(-pow((2*proList[j].e)/(float)(3*eMax),3))));
				}
				//heape atýlacak
				Insert(proList[j],H1);
			}
		}
		Item=FindMin(H1);
		if(Item.e>q){
					for(int k=0;k<count;k++){
 							if(strcmp(Item.name, proList[k].name) == 0){
 								proList[k].e=proList[k].e-q;
								proList[k].priority=proList[k].e*(1/(exp(-pow((2*proList[k].e)/(float)(3*eMax),3))));
							 }
		 				}
		 				i+=q;
			
	}
	else{
	     for(int k=0;k<count;k++){
 							if(strcmp(Item.name, proList[k].name) == 0){
 								i+=proList[k].e;
 								proList[k].e=0;
 								proList[k].waitTime=i-(proList[k].time+Item.eLast);
 								if(proList[k].waitTime<=0){
 									proList[k].waitTime=0;
								 }
								 printf("%d %s %d\n",i,proList[k].name,proList[k].waitTime);
								sumOfWaitTime+=proList[k].waitTime;
							 }
		 				}
		 				
	}
	Destroy(H1);
	if(i==totalTime){
		i++;
	}
}
printf("%d  AWT = %f\n",q, sumOfWaitTime/count);
}
return 0;
}
