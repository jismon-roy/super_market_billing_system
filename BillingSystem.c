		//bill
		#include <stdio.h>
		#include <string.h>
		#include <stdlib.h>
		#include <ctype.h>
		#include <time.h>
		char cdate[12] ,cntime[12];
		typedef struct  product
        {
	    int id;
	    char type[10];
	    char name[20];
	    int price;
	    int quantity;
	    int tax;
        }product;
		typedef struct 
		{
		int id;
		float tamt;
		char orprts[50],cname[20],date[11],cntime[5],qty[50],mrp[50],price[50],tax[50];
		}order;
		product findpro;
		int deleteing(int id,char name[20],char type[15],int tempflag);
		int checknumber(char string[20]);
		int updateproduct();
        int  itemcheck(int idno,char name[20],int temp);
		int searchpresence(FILE* fp,product addedpro);
		int checknumber(char string[20]);
		int  billcheck(int inputid);
		void dateandtime();
		int productmenu();
		int productsearch(int inputid);
		int  productqtycheck(int inputid,int qty);
		int diplayBill();
		int neworder();
		int deletebill();
		int Menu();//bill menu
		int addpro();
		int deleteproduct();
	
	    int updateqty(int products[50][2]);
		int findlastindex(FILE * p,char fname[20]);
		int main()
		{
			
		printf("================================================================================\n");
		printf("                                      WELCOME                                      \n");
		printf("================================================================================\n\n");
		printf("                           -->>ADHOLOKHAM SUPERMARKET<<--						  \n");
		printf("                                 Aluva,PH:9887766534                              \n");
		printf("================================================================================");
         Menu();
		
		return 0;
		}

int Menu(){
	int choice,back=0;
	do
		{
		//printf("================================================================================\n");
		printf("\n==================================>>Main Menu<<=================================\n");
		printf(" 1.Add Products\n\n 2.Update Products\n\n 3.Display Products\n\n 4.Delete products\n\n 5.New Bill\n\n 6.Display Bills \n\n 7.Delete a Bill\n\n 8.Exit.....!!\n\n Enter your choice:");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			back=addpro();			
			break;
			case 2:
			reupdate:
			back=updateproduct();
			if(back==1)
			goto reupdate;
			else
			back=0;	
			break;
			case 3:
			back=productmenu();
			break;
			case 4:
			back=deleteproduct();
			break;
			case 5:
			productmenu();
			back=neworder();
			break;
			case 6:
			back=diplayBill();
			break;
			case 7:
			back=deletebill();
			break;
			case 8:
			back=1;
			break;
			default:
			printf("Wrong input....");

			}
			
			}while(back==0);
			
		return 0;
			}
int  productsearch(int inputid){
		FILE* file;
		int flag=0,id;
		//int count=0,lid,lname,ltype,lprice,ltax,i;
		char name[20],type[20],price[5],tax[5];
		file = fopen("product.txt","r");
		if (file==NULL)
		{
		printf("unable to open the file");
		return 1;
		
		}
		char buffer[200];
		while (fgets(buffer, 255, (FILE*)file)!= NULL)
		{
		sscanf(buffer,"%d %s %s %s %s",&id,name,type,price,tax);
		if(inputid==id)
		{
		return 1;
		flag=1;
		break;
		}
		
		}
		if(flag==0){
		return 0;}
		fclose(file);
		
		}
int  billcheck(int inputid){
		FILE* file;
		int flag=0;
		order bc;
		
		char buffer[200];
		file=fopen("OrderBills.txt","r");
		while (fgets(buffer, 255, (FILE*)file)!= NULL)
		{
		sscanf(buffer,"%d %s %s %s %s %s %f %s\n",&bc.id,bc.cname,bc.orprts,bc.qty,bc.price,bc.tax,&bc.tamt,bc.date);
		if(inputid==bc.id)
		{ 
			fclose(file);
			return 0;
			}
			flag=1;
		}
		if(flag==1){
			fclose(file);
		return 1;}
		
		
		}
int  productqtycheck(int inputid,int qty){
		FILE* file;
		int flag=0,id,pqty;
		//int count=0,lid,lname,ltype,lprice,ltax,i;
		char name[20],type[20],price[5],tax[5];
		file = fopen("product.txt","r");
		if (file==NULL)
		{
		printf("unable to open the file");
		return 1;
		
		}
		char buffer[200];
		while (fgets(buffer, 255, (FILE*)file)!= NULL)
		{
		sscanf(buffer,"%d %s %s %s %s %d",&id,name,type,price,tax,&pqty);
		if(inputid==id)
		{
			
			if(pqty==0){
				fclose(file);
				return -1;
				flag=1;
				break;
				
				}else if(qty>pqty){
					fclose(file);
				return pqty;
				flag=1;
				break;
					}
			
		
		}
		
		}
		if(flag==0){
		fclose(file);
		return 0;}
		
		
		}		
int neworder()
		{
		int products[50][2],orno=1,arrsize=50,i,lindex=0,flag,sqty;
		FILE *orderp,*file,*tempp;
		char ch;
		order or={0};
		repeatorder:
		flag=0;
		printf("\n\n================================================================================\n\n");
		    printf("                                -->>PLACE ORDER<<--						 	  \n");
		    printf("================================================================================\n");
		printf("\nEnter the customer name: ");
		scanf("%s",or.cname);
		do
		{
		if(arrsize<0)
		{
		printf("Maximum products added on this Bill....Make another bill...!!!!");
		goto label;
				}
		else{
			reenterqty:
		printf("\nEnter the Product.No of the Product: ");
		scanf("%d",&products[orno][1]);
		if(productsearch(products[orno][1])==0)
		{
		printf("\nInvalid Product Id......!!!!\n");
		}else{
		printf("\nEnter the quantity of the Product: ");
		scanf("%d",&products[orno][2]);
		sqty=productqtycheck(products[orno][1],products[orno][2]);		
		if(sqty!=0){
			if(sqty==-1){sqty=0;}
			printf("\n\n                                  OUT OF STOCK\n\n                              only %d is available\n\n",sqty);
			goto reenterqty;
			}
		products[orno+1][1]=-1;
		orno++;
		arrsize--;}
		
		
		printf("\nDo you want to order another product(y/n): ");
		scanf("%s",&ch);
		
		}
		}while(ch=='Y' || ch=='y');
		label:
		orderp=fopen("OrderBills.txt","a");
		if (orderp==NULL)
		{
		printf("unable to open the file");
		return 0;
		}
		else{
		lindex=findlastindex(orderp,"OrderBills.txt");
		printf("\nDo you want to confirm this order(y/n):");
		scanf("%s",&ch);
		if(ch=='Y' || ch=='y')
		{
		//FILE* file;
		int id;float price,tax;
		char name[20],type[20];
		file = fopen("product.txt","r");
		if (file==NULL)
		{
		printf("unable to open the file");
		return 0;
		
		}
		char buffer[200];
		float itot;
		or.id=lindex+1;
		dateandtime();
		sscanf(cdate,"%s",or.date);
		sscanf(cntime,"%s",or.cntime);
		while (fgets(buffer, 255, (FILE*)file)!= NULL)
		{
		sscanf(buffer,"%d %s %s %f %f",&id,name,type,&price,&tax);
		for(i=1;products[i][1]!=-1;i++){
			if(id==products[i][1]){
		or.tamt=or.tamt+((price+(price*(tax/100)))*products[i][2]);}}
		
    }fclose(file);
    file = fopen("product.txt","r");
		if (file==NULL)
		{
		printf("unable to open the file");
		return 0;
		
		}
		while (fgets(buffer, 255, (FILE*)file)!= NULL)
		{
		sscanf(buffer,"%d %s %s %f %f",&id,name,type,&price,&tax);
		for(i=1;products[i][1]!=-1;i++){
		if(id==products[i][1]){
		
		
		itot=((price+(price*(tax/100)))*products[i][2]);
		fprintf(orderp,"%d %s %d %d %f %f %f %f %s\n",or.id,or.cname,id,products[i][2],price,tax,itot,or.tamt,or.date);
   }}}
		fclose(file);
		fclose(orderp);
		flag=1;
	  file = fopen("product.txt","r");
		if (file==NULL)
		{
		printf("unable to open the file");
		//return 1;
		
		
		}
		or.tamt=0;
		printf("================================================================================\n");
		printf("                       -->>ADHOLOKHAM SUPERMARKET<<--							 \n");
		printf("                            Aluva,PH:9887766534\n");
		printf("================================================================================\n");
		printf("INVOICE No:%d                                   GSTIN:32AJFPR338517L\n\n",or.id);
		printf("Customer Name:%s\n",or.cname);
		printf("================================================================================\n");
		printf("Item                MRP            Qty            Total            \n");
		printf("================================================================================\n");
		int count=0,lname,lQty,lprice,ltotal,j;float temp,ttax=0;
		char qty[20],itotal[20],iprice[20];
		while (fgets(buffer, 255, (FILE*)file)!= NULL)
		{
		sscanf(buffer,"%d %s %s %f %f",&id,name,type,&price,&tax);
		//printf("%d",id);
		for(i=1;products[i][1]!=-1;i++){
		if(id==products[i][1]){
			sscanf(qty,"%d",&products[i][2]);
			sscanf(iprice,"%f",&price);
			temp=((price+(price*(tax/100)))*products[i][2]);
			sscanf(itotal,"%f",&temp);
		lname=strlen(name);
		lprice=strlen(iprice);
		lQty=strlen(qty);
		ltotal=strlen(itotal);
		//printf("dhhfgsdjhfgjhfgjhg");
		printf("%s",name);
		for(j=0;j<20-lname;j++){printf(" ");}
		printf("%.2f",price);
		for(j=0;j<15-lprice;j++){printf(" ");}
		printf("%d",products[i][2]);
		for(j=0;j<15-lQty;j++){printf(" ");}
		printf("%.2f",(price+(price*(tax/100)))*products[i][2]);
		for(j=0;j<17-ltotal;j++){printf(" ");}
		ttax=tax+(price*(tax/100))*products[i][2];
        or.tamt=or.tamt+(price+(price*(tax/100)))*products[i][2];
		printf("\n\n");
		count++;
        }}}
		printf("================================================================================\n");
		printf("Date:%s                               GST:%.2f Rs\n\n",or.date,ttax);
		printf("Time:%s                           Total Amount:%.2f Rs\n\n",or.cntime,or.tamt);
		printf("================================================================================\n");
		printf("                                  VISIT AGAIN\n\n");
		fclose(file);
		
		
		
		}else{
		printf("================================================================================\n");
		printf("ORDER....CANCELLED.....!!!!!!!!!!\n");
		printf("================================================================================\n\n");
		orno=1,arrsize=50;for(i=0;i<50;i++){products[i][0]=0,products[i][1]=0,products[i][2]=0;}
		goto confrim;
		
		}
		
		
		}
		
		if(flag==1){
			 product p1;
		i=1;
		
		char buffer[200];
		file=fopen("product.txt","r");
		tempp=fopen("temp1.txt","w");
		while (fgets(buffer, 255, (FILE*)file)!= NULL)
		{
		
		sscanf(buffer,"%d %s %s %d %d %d\n",&p1.id,p1.name,p1.type,&p1.price,&p1.tax,&p1.quantity);
		
			
			if(p1.id==products[i][1]){
			fprintf(tempp,"%d %s %s %d %d %d\n",p1.id,strlwr(p1.name),strlwr(p1.type),p1.price,p1.tax,p1.quantity-products[i][2]);
			i++;
			}
			else{
			fprintf(tempp,"%d %s %s %d %d %d\n",p1.id,strlwr(p1.name),strlwr(p1.type),p1.price,p1.tax,p1.quantity);
			}
           
			
		}
		fclose(file);
		fclose(tempp);
		tempp=fopen("temp1.txt","r");
		file=fopen("product.txt","w");
		while (fgets(buffer, 255, (FILE*)tempp)!= NULL)
		{
		
		sscanf(buffer,"%d %s %s %d %d %d\n",&p1.id,p1.name,p1.type,&p1.price,&p1.tax,&p1.quantity);
		
			fprintf(file,"%d %s %s %d %d %d\n",p1.id,strlwr(p1.name),strlwr(p1.type),p1.price,p1.tax,p1.quantity);
			
           
			
		}
		fclose(file);
		
		
				
		 fclose(tempp);       
        remove("temp1.txt");
		//rename("temp1.txt","product.txt");
		
         }
		 
		
		char reorder;
		confrim:
		printf("Do you want to make another order(y/n):");
		scanf("%s",&reorder);
		//if(oc!=0 && ch=='n' || ch=='n'){return 0;}
		if(reorder=='y' || reorder=='Y'){
		orno=1,arrsize=50;for(i=0;i<50;i++){products[i][0]=0,products[i][1]=0,products[i][2]=0;}
		goto repeatorder;
		}else{
			return 0;
			}
		
		}
		
		
		
		int findlastindex(FILE * p,char fname[20])
		{
		int lindex=0,id=0;
		p=fopen(fname,"r");
		if (p==NULL)
		{
		//printf("unable to open the file");
		return 0;
		
		}
		else{
		char buffer[200];
		while (fgets(buffer, 255, (FILE*)p)!= NULL)
		{ 
			sscanf(buffer,"%d ",&id);
		lindex++;
		}
		//printf("%d",id);
		fclose(p);
		return id;
		
		}
		}
		
		
		
		int productmenu()
		{
		
		
		FILE* file;
		int count=0,lid,lname,ltype,lprice,ltax,lqty,i;
		char id[5],name[20],type[20],price[5],tax[5],qty[5];
		file = fopen("product.txt","r");
		if (file==NULL)
		{
		printf("unable to open the file");
		return 1;
		
		}
		printf("\n\n==============================================================================\n");
		printf("                                    PRODUCT MENU							   \n");
		//printf("===================================================================\n");
		printf("================================================================================\n");
		printf("Pr_Id     Pr_Name             Pr_type             Price       Tax       Qty       \n");
		printf("================================================================================\n");
		char buffer[200];
		while (fgets(buffer, 255, (FILE*)file)!= NULL)
		{
		sscanf(buffer,"%s %s %s %s %s %s",id,name,type,price,tax,qty);
		lid=strlen(id);lname=strlen(name);ltype=strlen(type);lprice=strlen(price);ltax=strlen(tax);lqty=strlen(qty);
		
		printf("%s",id);
		for(i=0;i<10-lid;i++){printf(" ");}
		printf("%s",name);
		for(i=0;i<20-lname;i++){printf(" ");}
		printf("%s",type);
		for(i=0;i<20-ltype;i++){printf(" ");}
		printf("%s",price);
		for(i=0;i<12-lprice;i++){printf(" ");}
		printf("%s",tax);
		for(i=0;i<10-ltax;i++){printf(" ");}
		printf("%s",qty);
		for(i=0;i<10-lqty;i++){printf(" ");}
		printf("\n\n");
		count++;
		
		}
		
		if(count==0){
		printf("No.......Data.....!!!!!!!!!!\n");
		printf("================================================================================\n");}
		else{
		printf("================================================================================\n");
		printf("%d Records\n\n",count);
		printf("================================================================================\n");}
		
		fclose(file);
		return 0;
		}
		
		void dateandtime(){
		int hours, minutes, seconds, day, month, year;    
		time_t now;  
		time(&now);
		struct tm *local = localtime(&now);
		
		hours = local->tm_hour;        
		minutes = local->tm_min;      
		seconds = local->tm_sec;        
		
		day = local->tm_mday;          
		month = local->tm_mon + 1;      
		year = local->tm_year + 1900;  
		if (hours < 12) {    
		sprintf(cntime,"%02d:%02d:%02d am", hours, minutes, seconds);
		}
		else {   
		sprintf(cntime,"%02d:%02d:%02d pm", hours - 12, minutes, seconds);
		}
		sprintf(cdate,"%02d-%02d-%d", day, month, year);
		//printf("%s %s",cdate,cntime);
		
		}
	int diplayBill(){
		FILE *bdis;
		order dor;
		char buffer[200],id[20],bid[5];
		int flag=0,lid,lname,ldate,i,lbid,count=0;
		float total=0;
		
		printf("\n================================================================================\n");
		printf("                                       BILLS\n");
		printf("================================================================================\n");
		printf("================================================================================\n");
		printf("B_id      Cst_Name             DATE             Bill_Amount    \n");
		printf("================================================================================\n");
		bdis=fopen("OrderBills.txt","r");
		if (bdis==NULL)
		{
		printf("unable to open the file");
		//return 1;
		}
		while (fgets(buffer, 255, (FILE*)bdis)!= NULL)
		{
		sscanf(buffer,"%s %s %s %s %s %s %f %f %s\n",bid,dor.cname,dor.orprts,dor.qty,dor.price,dor.tax,&dor.tamt,&total,dor.date);
		dor.id=atoi(bid);
		if(dor.id!=flag){
			
		sscanf(id,"%f",&total);
		lbid=strlen(bid);lid=strlen(id);lname=strlen(dor.cname);ldate=strlen(dor.date);		
		printf("%s",bid);
		for(i=0;i<10-lbid;i++){printf(" ");}
		printf("%s",dor.cname);
		for(i=0;i<20-lname;i++){printf(" ");}
		printf("%s",dor.date);
		for(i=0;i<20-ldate;i++){printf(" ");}
		printf("%.2f",total);
		for(i=0;i<15-lid;i++){printf(" ");}
		printf("\n\n");
		flag=dor.id;
		count++;
	}
	
	}
	
	if(count==0){
		printf("No.......Data.....!!!!!!!!!!\n");
		printf("================================================================================\n");}
		else{
		printf("================================================================================\n");
		printf("%d Records\n\n",count);
		printf("================================================================================\n");}
	fclose(bdis);
	return 0;
		}	
	
		
		
		
	int deletebill(){
		FILE *dlfilep,*tempf;
		order dor,dor1;
		char buffer[200],id[20];
		int flag=0,lid,lname,ldate,i,inputid;
		diplayBill();
	redelete:
	printf("\n================================================================================\n");
		printf("Enter the ID of Bill you need to Remove: ");
		scanf("%d",&inputid);
		if(billcheck(inputid)!=0){
			printf("\n\n Invalid Id.............!!!!!!!\n");
			printf("\n================================================================================\n");
			return 0;
			}
		dlfilep=fopen("OrderBills.txt","r");
		tempf=fopen("temp.txt","w");
		char abc[20];
		while (fgets(buffer, 255, (FILE*)dlfilep)!= NULL)
		{
		sscanf(buffer,"%d %s %s %s %s %s %f %s\n",&dor1.id,dor1.cname,dor1.orprts,dor1.qty,dor1.price,dor1.tax,&dor1.tamt,dor1.date);
		strcpy(abc,dor1.qty);
		if(inputid!=dor1.id)
		{ 
			//printf("dhfgdgyf");
			fprintf(tempf,"%d %s %s %s %s %s %f %s\n",dor1.id,dor1.cname,dor1.orprts,abc,dor1.price,dor1.tax,dor1.tamt,dor1.date);
			}
		}
		fclose(dlfilep);
		fclose(tempf);
		if (remove("OrderBills.txt") == 0){
		rename("temp.txt","OrderBills.txt");
		    printf("\n\n================================================================================\n");
		        printf("                          BILL SUCCESSFULLY REMOVED          					\n");
		    printf("================================================================================\n");}
		    dlfilep=fopen("OrderBills.txt","r");
		
		if (dlfilep==NULL)
		{
		printf("unable to open the file");
		//return 1;
		}
		printf("================================================================================\n");
		printf("Bill_Id     Cst_Name             DATE             \n");
		printf("================================================================================\n");
		while (fgets(buffer, 255, (FILE*)dlfilep)!= NULL)
		{
		sscanf(buffer,"%d %s %s %s %s %s %f %s\n",&dor.id,dor.cname,dor.orprts,abc,dor.price,dor.tax,&dor.tamt,dor.date);
		if(dor.id!=flag){
		sscanf(id,"%d",&dor.id);
		lid=strlen(id);lname=strlen(dor.cname);ldate=strlen(dor.date);		
		printf("%d",dor.id);
		for(i=0;i<12-lid;i++){printf(" ");}
		printf("%s",dor.cname);
		for(i=0;i<20-lname;i++){printf(" ");}
		printf("%s",dor.date);
		for(i=0;i<20-ldate;i++){printf(" ");}
		printf("\n\n");
		flag=dor.id;
	}
	}
	
	fclose(dlfilep);
	    char redelete;
		printf("Do you want to remove another bill(y/n):");
		scanf("%s",&redelete);
		
		if(redelete=='y' || redelete=='Y'){
		goto redelete;
		}else{
			return 0;
			}
		}
		
int deleteproduct(){
	 
    char name[20] ,types[15];
    int numcheck;
    int flag =0;
    label:
    printf("\n\n================================================================================\n");
    printf("\n                            PAGE FOR DELETION");
    while (flag == 0)
    {
        printf("\n================================================================================\n");
        printf("\nEnter a Name or Id  to delete: ");
         scanf("%s",name);
         numcheck = checknumber(name);
        if (numcheck ==0)
        {
                printf("Enter the type of the item: ");
                scanf("%s",types);
              // deleteing(0,name,type,0);
              deleteing(0,name,types,0);
              flag=1;
        }
         else if (numcheck == 1)
        {
           deleteing(atoi(name),"","",1);
           flag=1;
        }
       printf("\n\n================================================================================\n");

    }
    char redelete;
		printf("Do you want to delete another product(y/n):");
		scanf("%s",&redelete);
		
		if(redelete=='y' || redelete=='Y'){
			flag=0;
		goto label;
		}else{
			return 0;
			}
    

	}		
		

int addpro(){
	product p;
    int flag =0;
    int pro ;
   
  FILE* file ;
  label: 
  printf("\nADDING A NEW STOCK SECTION \n");
  while (flag==0)   // repeating the loop for  adding the data continuously
  {

       file = fopen("product.txt","a+");
        if (file == NULL)
         {
              printf("unable to open the file ");
              return 0;

        }



      
    printf("================================================================================");
    printf("\nEnter the id of the product:");
    scanf("%d",&p.id);
     printf("\nEnter the type of the product:");
      scanf("%s",p.type);
     printf("\nEnter the name of the product:");
    scanf("%s",p.name);
     printf("\nEnter the price of the product:");
    scanf("%d",&p.price);
    printf("\nEnter the tax of the product:");
    scanf("%d",&p.tax);
    printf("\nEnter the quantity of the product:");
    scanf("%d",&p.quantity);
    printf("========================================================================");
    printf("\nid: %d name: %s type: %s price: %d quantity: %d \n\n",p.id,p.name,p.type,p.price,p.quantity);
    

   printf("========================================================================");
    
    pro = searchpresence(file,p);  // calling the function to scan database
    if (pro == 0)
    {
        printf("\nsorry, FAILED TO SAVE DATA\n\n");
    }
    else {
        fprintf(file,"%d %s %s %d %d %d\n",p.id,strlwr(p.name),strlwr(p.type),p.price,p.tax,p.quantity);
        printf("\n DATA SAVED SUCCEFULLY\n\n");
        flag=1;
            }
    
 
    
  }
  fclose(file);
      char readd;
		printf("Do you want to add another product(y/n):");
		scanf("%s",&readd);
		
		if(readd=='y' || readd=='Y'){
			flag=0;
		goto label;
		}else{
			return 0;
			}
	}
	
	
	
int deleteing(int id,char name[20],char type[15],int tempflag)
{
    FILE *file,*fp;
    char buffer[200];
    int fdvalue =0;
    product p;
    file = fopen("product.txt","r");
    fp = fopen("temp.txt","a+");
    if (file==NULL)
    {
        printf("unable to open the file ");
        return 0;
    }
    fgets(buffer,200,file);
    while (!feof(file))
    {
        sscanf(buffer,"%d %s %s %d %d %d\n",&p.id,p.name,p.type,&p.price,&p.tax,&p.quantity);
        
      if (tempflag==0 && (strcmp(strlwr(name),p.name)!=0 || strcmp(strlwr(type),p.type)!=0))
      {
          //  printf("\nentering the if copy  %s\n",p.name);
         fprintf(fp,"%d %s %s %d %d %d\n",p.id,p.name,p.type,p.price,p.tax,p.quantity);
         
      }
      else if (tempflag == 1 && p.id != id)
      {
           
         fprintf(fp,"%d %s %s %d %d %d\n",p.id,p.name,p.type,p.price,p.tax,p.quantity);
      }
      
      else if(strcmp(strlwr(name),p.name)==0 && strcmp(strlwr(type),p.type)==0 )//checking weather the strings are same or not
         {
         //  printf("\nfinded pro== %s %s \n",p.name,p.type);
             fdvalue = 1;
         }
        else if (tempflag ==1 && p.id == id)
        {
         
            fdvalue = 1;
        }
   
      
         
      fgets(buffer,200,file);
    }

    fclose(file);
    fclose(fp);
    if (fdvalue == 1)
    {
         remove("product.txt");
         rename("temp.txt","product.txt");
         printf("\n================================================================================\n");
         printf("                              SUCCESSFULLY DELETED");
    }
    else if(fdvalue == 0)
    {
     //   printf("\nentering the if ++++++++++\n");
        if (tempflag == 1)
        {
           printf("\nsorry, unable to find the item with id : %d",id);
        }
        else if (tempflag ==0)
        {
          printf("\nsorry, unable to find the item with name : %s",name);
        }
        
        remove("temp.txt");
    }
    
   
    
    

}

int searchpresence(FILE* fp,product addedpro)  // function definition
{
    product p;
   
     char buffer[200];
     fgets(buffer,200,fp);
     while (!feof(fp))
     {
         sscanf(buffer,"%d %s %s %d",&p.id,p.name,p.type,&p.price);

         if(strcmp(strlwr(p.name),strlwr(addedpro.name))==0 && strcmp(strlwr(p.type),strlwr(addedpro.type))==0)//checking weather the name are same or not
         {
              printf("\n id: %d name: %s type: %s price: %d  --is already present\n ", p.id,p.name,p.type,p.price);
              
             printf("-----------------------------------------------------------------------");
              printf("\nItem is already present ");
              return 0;
         }
         else if(p.id == addedpro.id)
         {
             printf("\nid: %d name: %s type: %s price: %d\n --is already present\n ",p.id,p.name,p.type,p.price);
                
              printf("-----------------------------------------------------------------------");
             printf("\nPlease enter a new id\n");
              return 0;
         }
        
         fgets(buffer,200,fp);
     }
     return 1;
}
int checknumber(char string[20])
{
    if (isdigit(string[0]))
    {
        return 1;
    }
    return 0;
    
}
	
int updateproduct()
{
	int c;
	
    int temp,checkval,convertedint;
    char proids[20];
  
	begin:	
	 printf("\n================================================================================\n");
	printf("Enter product id to update: ");
	scanf("%s",proids);
    checkval = checknumber(proids);
    if (checkval==1)
    {
       convertedint = atoi(proids);
       goto label;
    }else
    {
        printf("DISPLAYING THE DETAILS OF %s\n",proids);
        itemcheck(0,proids,0);
        printf("\nPLEASE ENTER AN ID TO UPDATE THE STOCK\n");
        goto begin;
    }
    
  label:  itemcheck(convertedint,"",1);
   
   		if(findpro.id==convertedint) 
		{
           deleteing(convertedint,"","",1);
            FILE *file;
        	 file=fopen("product.txt","a+");
        	if (file==NULL)
        	{
        		printf("file cant be opened");
	        	return 0;
        	}
			
		    printf("\n1.Change Price");
		    printf("\n2.Change Tax");
		    printf("\n3.Change Quantity");
			printf("\n4.Exit");
    		printf("\nEnter Your Choice: ");
			scanf("%d",&c);
			switch(c)
			{
            
            	case 1: printf("\nENTER NEW PRICE: ");
						scanf("%d",&findpro.price);
                        fprintf(file,"%d %s %s %d %d %d\n",findpro.id,strlwr(findpro.name),strlwr(findpro.type),findpro.price,findpro.tax,findpro.quantity);
                         printf("\n================================================================================\n");
                         printf("                                SUCCESSFULLY UPDATED\n");
                         printf("\n================================================================================\n");
						break;
				case 2: printf("\nENTER NEW TAX: ");
						scanf("%d",&temp);
                        fprintf(file,"%d %s %s %d %d %d\n",findpro.id,strlwr(findpro.name),strlwr(findpro.type),findpro.price,temp,findpro.quantity);
                         printf("\n================================================================================\n");
                         printf("                                SUCCESSFULLY UPDATED\n");
                         printf("\n================================================================================\n");
						break;
								
				case 3: printf("\nENTER THE QUANTITY YOU NEED TO ADD: ");
						scanf("%d",&temp);
                        findpro.quantity+=temp;
                        fprintf(file,"%d %s %s %d %d %d\n",findpro.id,strlwr(findpro.name),strlwr(findpro.type),findpro.price,findpro.tax,findpro.quantity);
                         printf("\n================================================================================\n");
                         printf("                                SUCCESSFULLY UPDATED\n");
                         printf("\n================================================================================\n");
						break;
				
				case 4: printf("\n");
                         fprintf(file,"%d %s %s %d %d %d\n",findpro.id,strlwr(findpro.name),strlwr(findpro.type),findpro.price,findpro.tax,findpro.quantity);
						break;
						
				default:printf("\nOPTION NOT AVAILABLE..........!!!");
                 fprintf(file,"%d %s %s %d %d %d\n",findpro.id,strlwr(findpro.name),strlwr(findpro.type),findpro.price,findpro.tax,findpro.quantity);
						break;
			}
            
            fclose(file);
            
            char redelete;
		printf("Do you want to update another product(y/n):");
		scanf("%s",&redelete);
		
		if(redelete=='y' || redelete=='Y'){
			return 1;
		}else{
			return 0;
			}
		}

   
   
}

int itemcheck(int idno,char name[20],int temp)  // checking the value and return the specific value
{
     
     FILE* file;
   //product p;
   int i;
   char  findlength[20]; 
     file = fopen("product.txt","r");
     if (file==NULL)
     {
         printf("unable to open the file");
         return 0 ;

     }
     
     int flag =0 ;
     char buffer[200];
     fgets(buffer,200,file);
        printf("\n================================================================================\n");
     while (!feof(file))
     {
         sscanf(buffer,"%d %s %s %d %d %d",&findpro.id,findpro.name,findpro.type,&findpro.price,&findpro.tax,&findpro.quantity);
        if (temp==0 &&(strcmp(findpro.name,strlwr(name))==0 || strcmp(findpro.type,strlwr(name))==0))
        {

            printf("\n\n id: %d",findpro.id);
               itoa(findpro.id,findlength,20);
               for (i = 0; i < 12-strlen(findlength); i++) { printf(" "); }
                       
            printf("name: %s",findpro.name);
           for (i = 0; i < 12-strlen(findpro.name); i++) { printf(" "); }
            printf("type: %s",findpro.type);
            for (i = 0; i < 12-strlen(findpro.type); i++) { printf(" "); }
            printf("price: %d",findpro.price);
             itoa(findpro.price,findlength,20);
               for (i = 0; i < 12-strlen(findlength); i++) { printf(" "); }
               printf("Tax: %d",findpro.tax);
             itoa(findpro.tax,findlength,20);
               for (i = 0; i < 12-strlen(findlength); i++) { printf(" "); }
            printf("quantity: %d",findpro.quantity);
             itoa(findpro.quantity,findlength,20);
               for (i = 0; i < 12-strlen(findlength); i++) { printf(" "); }
             
            flag =1;
             
         }
        else if (temp == 1 && idno ==findpro.id)
         {
            
              printf("id: %d  name: %s  type: %s  price: %d  Tax: %d  quantity: %d \n\n ",findpro.id,findpro.name,findpro.type,findpro.price,findpro.tax,findpro.quantity);
              fclose(file);
              return 1;
         }
         
        
         fgets(buffer,200,file);
     }
     if (flag !=1 )
     {
          printf("\n\n================================================================================\n");
        printf("please enter a valid id\n");
     }
     
     
     fclose(file);
     return 0;
}

		
		
