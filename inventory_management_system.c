//Inventory management system in the C language using file handling and custom output    
    #include<stdio.h>
    #include<conio.h>
    #include<process.h>
    #include<float.h>
    #include<windows.h>
    #include<string.h>
    #define INVALID printf("\nInvalid choice..."); getche(); exit(0);
    #define FILE_HANDLING_ERROR printf("An error occurred while handling a file");
    #define MAX 100
    
    typedef struct product
    {
    char SKU[5];
    int sl_no;
    char name[10];
    float price;
    char batch[12];
    int quantity;
    }product;
    
    void gotoxy(short int col,short int row)
    {
         HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
         COORD position={col,row};
         SetConsoleCursorPosition(hStdout,position);
    }
    
    
    void modify(char mod_val[],char new_sku[],char name[],char batch[],int quantity,float price,int sl_no)
    {
    FILE *fp,*temp;
    product t_rec;
    int ctr_h=0,ctr_v=0;
    fp=fopen("DATA.txt","rb");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    temp=fopen("TEMP.txt","wb");
    if(temp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    ctr_h=0;
    while(fread(&t_rec,sizeof(struct product),1,fp))
    {
    ctr_h++;                                  
    if(strcmp(t_rec.SKU,mod_val)==0)
    {
                                    strcpy(t_rec.SKU,new_sku);
                                    t_rec.sl_no=sl_no;
                                    strcpy(t_rec.name,name);
                                    strcpy(t_rec.batch,batch);
                                    t_rec.price=price;  
                                    t_rec.quantity=quantity;
                                    fwrite(&t_rec,sizeof(struct product),1,temp);
    }
    else
    fwrite(&t_rec,sizeof(struct product),1,temp);
    }
    fclose(temp);
    fclose(fp);
    }
    if(ctr_h==0)
    {
    printf("NO MATCHES FOUND..");
    }
    else
    {
    remove("DATA.txt");
    rename("TEMP.txt","DATA.txt");
    printf("\nProduct Succesfully Modified...");
    }
    }
    }     
    
    void draw_vertical(int ctr_var)
    {
    int j;
    for(j=0;j<ctr_var;j++)
    {
    gotoxy(7,j);
    printf("|");
    }
    
    for(j=0;j<ctr_var;j++)
    {
    gotoxy(20,j);
    printf("|");
    }
     for(j=0;j<ctr_var;j++)
    {
    gotoxy(35,j);
    printf("|");
    }
    for(j=0;j<ctr_var;j++)
    {
    gotoxy(50,j);
    printf("|");
    }
    for(j=0;j<ctr_var;j++)
    {
    gotoxy(68,j);
    printf("|");
    }
    }
    
    void draw_horizontal_line(int ctr_var)
    {
    int i=0;
    gotoxy(0,ctr_var);
    for(i=0;i<79;i++)
    printf("-");
    }
    
         
    void display(product prod,int ctr)
    {
    int i;
    printf("\n");
    for(i=0;i<75;i++)
    {
    printf("-");
    }
    gotoxy(1,ctr);   
    printf("%-5s",prod.SKU);
    gotoxy(10,ctr);
    printf("%5d",prod.sl_no);
    gotoxy(24,ctr);
    if(strlen(prod.name)>=6)
    printf("%-10s",prod.name);
    else
    {
    gotoxy(26,ctr);
    printf("%-6s",prod.name);
    }
    gotoxy(36,ctr);
    if(strlen(prod.batch)>=8)
    printf("%12s",prod.batch);
    else
    {
    gotoxy(40,ctr);
    printf("%-8s",prod.batch);
    }
    gotoxy(54,ctr);
    printf("%-f",prod.price);
    gotoxy(74,ctr);    
    printf("%d",prod.quantity);
    }
        
    void filter_s(char string[],int f,int sf)
    {
    FILE *fp,*temp;
    product t_rec;
    int ctr_h=0,ctr_v=0;
    fp=fopen("DATA.txt","rb");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    temp=fopen("TEMP.txt","wb");
    if(temp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    ctr_h=0;
    if(f==2)
    {
    while(fread(&t_rec,sizeof(struct product),1,fp))
    {
    if(sf==1)
    {             
    if(strcmpi(t_rec.name,string)<0)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    }
    else if(sf==2)
    {
    if(strcmpi(t_rec.name,string)==0)
    {
                fwrite(&t_rec,sizeof(struct product),1,temp);
                ctr_h++;
    }
    } 
    
    else if(sf==3)
    {
    if(strcmpi(t_rec.name,string)>0)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    }
    } 
    }
    else if(f==4)
    {
    ctr_h=0;
    while(fread(&t_rec,sizeof(struct product),1,fp))
    {              
    if(strcmpi(t_rec.batch,string)==0)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    } 
    }  
    fclose(temp);
    }
    fclose(fp);
    if(ctr_h==0)
    {
    printf("NO MATCHES FOUND..");
    }
    else
    {
    fp=fopen("TEMP.txt","rb");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    ctr_h=0;
    ctr_v=0;
    system("cls");
    gotoxy(2,1);
    printf("SKU");
    gotoxy(10,1);
    printf("SERIAL #");
    gotoxy(26,1);
    printf("NAME");
    gotoxy(40,1);
    printf("BATCH");
    gotoxy(57,1);
    printf("PRICE");
    gotoxy(70,1);
    printf("QUANTITY");
    draw_horizontal_line(3);
    ctr_h=4;
    while(fread(&t_rec,sizeof(product),1,fp))
    {                                         
    printf("\n");
    display(t_rec,ctr_h);
    draw_horizontal_line(ctr_h+1);
    ctr_h=ctr_h+2;
    ctr_v++;
    }
    draw_vertical((ctr_v*2)+4);
    }
    fclose(fp);
    }
    }
    }
    
    void del_record(char del_val[])
    {
    FILE *fp,*temp;
    product t_rec;
    int ctr_h=0,ctr_v=0;
    fp=fopen("DATA.txt","rb");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    temp=fopen("TEMP.txt","wb");
    if(temp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    ctr_h=0;
    while(fread(&t_rec,sizeof(struct product),1,fp))
    {  
    if(strcmp(t_rec.SKU,del_val)==0)
    {
         ctr_h++;
    }
    else
    {
         fwrite(&t_rec,sizeof(struct product),1,temp);
    }
    }
    fclose(temp);
    fclose(fp);
    }
    if(ctr_h==0)
    {
    printf("NO MATCHES FOUND..");
    }
    else
    {
    remove("DATA.txt");
    rename("TEMP.txt","DATA.txt");
    printf("\nProduct Succesfully Deleted...");
    }
    }
    }
     
    void filter_p(float x,int sf)
    {
    FILE *fp,*temp;
    product t_rec;
    int ctr_v,ctr_h=0;
    fp=fopen("DATA.txt","rb");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    temp=fopen("TEMP.txt","wb");
    if(temp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    ctr_h=0;
    while(fread(&t_rec,sizeof(struct product),1,fp))
    {
    if(sf==1)
    {             
    if(t_rec.price<x)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    }
    else if(sf==2)
    {
    if(t_rec.price==x)
    {
                fwrite(&t_rec,sizeof(struct product),1,temp);
                ctr_h++;
    }
    }
    else if(sf==3)
    {
    if(t_rec.price>x)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    }
    }
    fclose(temp);
    }
    if(ctr_h==0)
    {
    printf("NO MATCHES FOUND..");
    }
    else
    {
    fp=fopen("TEMP.txt","rb");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    ctr_h=0;
    ctr_v=0;
    system("cls");
    gotoxy(2,1);
    printf("SKU");
    gotoxy(10,1);
    printf("SERIAL #");
    gotoxy(26,1);
    printf("NAME");
    gotoxy(40,1);
    printf("BATCH");
    gotoxy(57,1);
    printf("PRICE");
    gotoxy(70,1);
    printf("QUANTITY");
    draw_horizontal_line(3);
    ctr_h=4;
    while(fread(&t_rec,sizeof(product),1,fp))
    {
    printf("\n");
    display(t_rec,ctr_h);
    draw_horizontal_line(ctr_h+1);
    ctr_h=ctr_h+2;
    ctr_v++;
    }
    draw_vertical((ctr_v*2)+4);
    }
    fclose(fp);
    }
    }
    }
    
    void filter(int x,int f,int sf)
    {
    FILE *fp,*temp;
    product t_rec;
    int ctr_h=0,ctr_v=0;
    fp=fopen("DATA.txt","rb");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    temp=fopen("TEMP.txt","wb");
    if(temp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    if(f==1)
    {
    ctr_h=0;
    while(fread(&t_rec,sizeof(struct product),1,fp))
    {
    if(sf==1)
    {              
    if(t_rec.sl_no<x)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    }
    else if(sf==2)
    {
    if(t_rec.sl_no==x)
    {
                fwrite(&t_rec,sizeof(struct product),1,temp);
                ctr_h++;
    }
    } 
    
    else if(sf==3)
    {
    if(t_rec.sl_no>x)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    }
    } 
    }
    else if(f==5)
    {
    ctr_h=0;
    while(fread(&t_rec,sizeof(struct product),1,fp))
    {
    if(sf==1)
    {              
    if(t_rec.quantity<x)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    }
    else if(sf==2)
    {
    if(t_rec.quantity==x)
    {
                fwrite(&t_rec,sizeof(struct product),1,temp);
                ctr_h++;
    }
    } 
    else if(sf==3)
    {
    if(t_rec.quantity>x)
    {
               fwrite(&t_rec,sizeof(struct product),1,temp);
               ctr_h++;
    }
    }
    }
    }   
    fclose(temp);
    }
    if(ctr_h==0)
    {
    printf("NO MATCHES FOUND..");
    }
    else
    {
    fp=fopen("TEMP.txt","rb");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    ctr_h=0;
    ctr_v=0;
    system("cls");
    gotoxy(2,1);
    printf("SKU");
    gotoxy(10,1);
    printf("SERIAL #");
    gotoxy(26,1);
    printf("NAME");
    gotoxy(40,1);
    printf("BATCH");
    gotoxy(57,1);
    printf("PRICE");
    gotoxy(70,1);
    printf("QUANTITY");
    draw_horizontal_line(3);
    ctr_h=4;
    while(fread(&t_rec,sizeof(product),1,fp))
    {
    printf("\n");
    display(t_rec,ctr_h);
    draw_horizontal_line(ctr_h+1);
    ctr_h=ctr_h+2;
    ctr_v++;
    }
    draw_vertical((ctr_v*2)+4);
    }
    fclose(fp);
    }
    }
    }
   
    
    static void force_fpf()
    {
    float x,*y;
    y=&x;
    x=*y;
    }
    
    int sub_filter_menu()
    {
    int choice;
    system("cls");
    printf("\n");
    printf("1.Lesser than(<X)");
    printf("\n");
    printf("2.Equal to(=X)");
    printf("\n");
    printf("3.Greater than(>X)");
    printf("\n");
    printf("\nEnter your choice ");
    scanf("%d",&choice);
    if(choice<0 || choice>3)
    {
    INVALID
    }
    else
    return choice;
    }
    
    
    void filter_menu()
    {
    char choice,ch='y';
    int i,j,ser_no,quantity,sf;
    char name[10],batch[12];
    float price;
    do
    {
    system("cls");
    printf("\n\n\n\n\n\t\t\t\t");
    printf("Filter by :-");
    printf("\n\t\t\t\t");
    printf("1.Serial #");
    printf("\n\t\t\t\t");
    printf("2.Name");
    printf("\n\t\t\t\t");
    printf("3.Price");
    printf("\n\t\t\t\t");
    printf("4.Batch");
    printf("\n\t\t\t\t");
    printf("5.Quantity");
    printf("\n\t\t\t\t");
    printf("Enter your choice");
    choice=getche();
    if(choice<48 || choice>53)
    {
    INVALID
    }
    
    else
    {
    switch(choice)
    {
    case '1':
    system("cls");
    printf("\n");
    sf=sub_filter_menu();
    printf("\nPlease enter the serial number of the product ");
    scanf("%d",&ser_no);
    filter(ser_no,1,sf);
    break;
    case '2':
    system("cls");
    printf("\n");
    sf=sub_filter_menu();
    printf("\nPlease enter the name of the product ");
    scanf("%s",name);
    filter_s(name,2,sf);
    break;     
    case '3':
    system("cls");
    printf("\n");
    sf=sub_filter_menu();
    printf("\nPlease enter the price of the product ");
    scanf("%f",&price);
    filter_p(price,sf);
    break;
    case '4':
    system("cls");
    printf("\n");
    printf("\nPlease enter the batch the product belongs to ");
    scanf("%s",batch);
    filter_s(batch,4,0);
    break;
    case '5':
    system("cls");
    printf("\n");
    sf=sub_filter_menu();
    printf("\nPlease enter the number of products (quantity) ");
    scanf("%d",&quantity);
    filter(quantity,5,sf);
    break;  
    break;     
    default:
    INVALID
    }
    
    }
    printf("\nfilter again?");
    ch=getche();
    }while(ch=='y' || ch=='Y');
    getche();
    }
    
    int main()
    {
    char choice,name[10],batch[12],new_SKU[5],new_name[10],new_batch[12],SKU[5],ch='y';
    int i,j,n,ctr_h=0,ctr_v,new_sl_no,new_quantity;
    float new_price;
    product prod[MAX],temp,temp1;
    FILE *fp,*fp1;
    do
    {
    system("cls");
    printf("\n\n\n\n\n\n\t\t\t\t");
    printf("1.APPEND");
    printf("\n\n\t\t\t\t");
    printf("2.DISPLAY");
    printf("\n\n\t\t\t\t");
    printf("3.FILTER");
    printf("\n\n\t\t\t\t");
    printf("4.DELETE");
    printf("\n\n\t\t\t\t");
    printf("5.MODIFY");
    printf("\n\n\t\t\t\t");
    printf("6.EXIT");
    printf("\n\n\t\t\t\t");
    printf("Enter your choice ");
    choice=getche();
    if(choice<48 || choice>54)
    {
    INVALID
    }
    
    else
    {
    switch(choice)
    {
    case '1':
    system("cls");
    printf("\n\n\t\tEnter the number of records\n\n\t\t");
    scanf("%d",&n);
    fp=fopen("Data.txt","ab");
    if(fp==NULL)
    FILE_HANDLING_ERROR
    else
    {
    for(i=0;i<n;i++)
    {
    system("cls");
    printf("\n\n\t\t");
    printf("PROD %d",i+1);  
    printf("\n\n\t\t");
    printf("Enter serial number ");
    scanf("%d",&prod[i].sl_no);
    printf("\n\t\t");
    printf("Enter name ");
    scanf("%s",prod[i].name);
    printf("\n\t\t");
    printf("Enter price ");
    scanf("%f",&prod[i].price);
    printf("\n\t\t");
    printf("Enter the batch(dd-mm-yyyy) ");
    scanf("%s",prod[i].batch);
    printf("\n\t\t");
    printf("Enter quantity ");
    scanf("%d",&prod[i].quantity);
    prod[i].SKU[0]=prod[i].name[0];
    prod[i].SKU[1]=prod[i].name[1];
    prod[i].SKU[2]=prod[i].batch[0];
    prod[i].SKU[3]=prod[i].batch[1];
    prod[i].SKU[4]='\0';
    }
    fwrite(&prod,sizeof(product),n,fp);
    fclose(fp);
    }
    break;
    
    case '2':
    system("cls");
    gotoxy(2,1);
    printf("SKU");
    gotoxy(10,1);
    printf("SERIAL #");
    gotoxy(26,1);
    printf("NAME");
    gotoxy(40,1);
    printf("BATCH");
    gotoxy(57,1);
    printf("PRICE");
    gotoxy(70,1);
    printf("QUANTITY");
    draw_horizontal_line(3);
    fp1=fopen("Data.txt","rb");
    if(fp1==NULL)
    {
    FILE_HANDLING_ERROR
    }
    else
    {
    ctr_v=0;
    ctr_h=4;
    while(fread(&temp,sizeof(product),1,fp1))
    {
    printf("\n");
    display(temp,ctr_h);
    draw_horizontal_line(ctr_h+1);
    ctr_h=ctr_h+2;
    ctr_v++;
    }
    draw_vertical((ctr_v*2)+4);
    }
    fclose(fp1);
    break;
    case '3':
    filter_menu();
    break;
    case '4':
    system("cls");
    printf("\nEnter the name of the product you wish to delete: ");
    scanf("%s",name);
    printf("\nEnter the batch of the product you wish to delete: ");
    scanf("%s",batch);
    SKU[0]=name[0];
    SKU[1]=name[1];
    SKU[2]=batch[0];
    SKU[3]=batch[1];
    SKU[4]='\0';
    del_record(SKU);
    break;
    case '5':
    system("cls");
    printf("\nEnter the name of the product you wish to modify: ");
    scanf("%s",name);
    printf("\nEnter the batch of the product you wish to modify: ");
    scanf("%s",batch);
    SKU[0]=name[0];
    SKU[1]=name[1];
    SKU[2]=batch[0];
    SKU[3]=batch[1];
    SKU[4]='\0';
    printf("\n\n\t\t Please enter the required changes...");  
    printf("\n\n\t\t");
    printf("Enter serial number ");
    scanf("%d",&new_sl_no);
    printf("\n\t\t");
    printf("Enter name ");
    scanf("%s",new_name);
    printf("\n\t\t");
    printf("Enter price ");
    scanf("%f",&new_price);
    printf("\n\t\t");
    printf("Enter the batch(dd-mm-yyyy) ");
    scanf("%s",new_batch);
    printf("\n\t\t");
    printf("Enter quantity ");
    scanf("%d",&new_quantity);
    new_SKU[0]=new_name[0];
    new_SKU[1]=new_name[1];
    new_SKU[2]=new_batch[0];
    new_SKU[3]=new_batch[1];
    new_SKU[4]='\0';
    modify(SKU,new_SKU,new_name,new_batch,new_quantity,new_price,new_sl_no);
    break;
    case '6':
    exit(0);
    break;
    default:
    INVALID
    }
    }
    printf("\n\nDo you wish to continue?");
    ch=getche();
    }while(ch=='y' || ch=='Y');
    return 0;
    }
    
   
