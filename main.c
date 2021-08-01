#include <stdio.h>
#include <stdlib.h>
float donation,income,total;
int i,shopping[16];
struct node
{
    char name[10],category;
    int serial,quantity;
    float price;
    struct node* next,* prev;
};
struct node* start,* end;

void init_node()
{
    start=end='\0';
}

struct node* create_node(char n[10],float p,int quan,int sn,char cat)
{
    struct node*ptr;
    ptr=(struct node*)malloc(sizeof(struct node));
    ptr->price=p;
    ptr->serial=sn;
    ptr->quantity=quan;
    strcpy(ptr->name,n);
    ptr->category=cat;
    ptr->next='\0';
    ptr->prev='\0';
    return ptr;
}

void insert_node(struct node*ptr)
{
    struct node* temp;
    temp=start;
    if (start=='\0'&&end=='\0')
    {
        start=end=ptr;
    }
    else
    {
        while(temp!='\0'&&temp->price<ptr->price)
        {
            temp=temp->next;
        }
        if(temp=='\0')
        {
            ptr->prev=end;
            end->next=ptr;
            end=ptr;
        }
        else if (temp==start)
        {
            start=ptr;
            temp->prev=ptr;
            ptr->next=temp;
        }
        else if(temp!='\0')
        {
            temp->prev->next=ptr;
            ptr->next=temp;
            ptr->prev=temp->prev;
            temp->prev=ptr;
        }
    }
}

struct node* search_node_sn(int n)
{
    struct node* temp;
    temp=start;
    while(temp!='\0')
    {
        if(temp->serial==n)
            break;
        else
        {
            temp=temp->next;
        }
    }
    return temp;
}

struct node* search_node(char n[10])
{
    struct node* temp;
    temp=start;
    while(temp!='\0')
    {
        if(strcmp(temp->name,n)==0)
            break;
        else
        {
            temp=temp->next;
        }
    }
    return temp;
}

void search (int w)
{
    int x,serial;
    char r,name[10];
    struct node* temp;
    printf("\t\tsearch\n\nsearch by:\n1-name\n2-serial number\n");
    scanf("%d",&x);
    switch(x)
    {
    case 1:
        printf("type the name of the product: ");
        scanf("%s",&name);
        temp=search_node(name);
        break;
    case 2:
        printf("type the serial number: ");
        scanf("%d",&serial);
        temp=search_node_sn(serial);
        break;
    default :
        printf("\t\tERROR\n");
        break;
    }
    if(x==1||x==2)
    {
        if (temp=='\0')
        {
            printf("not found\n");
        }
        else
        {
            printf("\n%s\t\t%f egp\t\t%d left in the machine\t\t#SN:%d\n",temp->name,temp->price,temp->quantity,temp->serial);
            if (w==1)
            {
                printf("\npress y to buy it or any key to continue\n");
                r=getch();
                if (r=='y'||r=='Y')
                {
                    sell(temp);
                }
            }
        }
    }
}

void delete_node(int n)
{
    char r;
    struct node* temp;
    temp=search_node_sn(n);
    if (temp=='\0')
    {
        printf("not found\n");
    }
    else
    {
        printf("are you sure you want to delete %s\npress y to delete or any key to cancel\n",temp->name);
        r=getch();
        if(r=='y'||r=='Y')
        {
            if (start==end)
            {
                destroy_list();
            }
            else if (temp==end)
            {
                end=temp->prev;
                end->next='\0';
                free(temp);
            }
            else if (temp==start)
            {
                start=temp->next;
                start->prev='\0';
                free(temp);
            }
            else
            {
                temp->prev->next=temp->next;
                temp->next->prev=temp->prev;
                free(temp);
            }
            printf("\ndone\n");
        }
    }
}

void destroy_list()
{
    struct node*temp=start;
    while(temp!='\0')
    {
        free(temp);
        temp=temp->next;
    }
    start='\0';
    end='\0';
}

void print_list_price(int w)
{
    struct node*temp;
    int x,z,num,i=1;
    char cat;
    printf("1-show all\n2-snacks\n3-beverages\n4-cigarettes\n");
    scanf("%d",&z);
    switch(z)
    {
    case 1:
        cat='\0';
        break;
    case 2:
        cat='s';
        break;
    case 3:
        cat='b';
        break;
    case 4:
        cat='c';
        break;
    default:
        return 0;
    }
    printf("_________________________________________________________________________\n1-from low price to high price\n2-from high price to low price\n");
    scanf("%d",&x);
    if(x==1||x==2)
    {
        printf("_________________________________________________________________________\n\t\t\tMENU");
        switch(cat)
        {
        case 's':
            printf("-'snacks'\n\n");
            break;
        case 'b':
            printf("-'beverages'\n\n");
            break;
        case 'c':
            printf("-'cigarettes'\n\n");
            break;
        default :
            printf("\n\n");
        }
    }
    switch(x)
    {
    case 1:
        temp=start;
        while (temp!='\0')
        {
            if (z==1)
            {
                cat=temp->category;
            }
            if (cat==temp->category)
            {
                printf("%d-%s\n\t\t%f egp\t\t%d left in the machine\t\t#SN:%d\n\n",i,temp->name,temp->price,temp->quantity,temp->serial);
                i++;
            }
            temp=temp->next;
        };
        if (w==1)
        {
            printf("\nwhich one do you want?\t\t\tpress 0 to go back\n");
            scanf("%d",&num);
            if (num==0)
                break;

            else
            {
                i=1;
                temp=start;
                if (z==1)
                {
                    while (temp!='\0'&&i!=num)
                    {
                        i++;
                        temp=temp->next;
                    }
                }
                else
                {
                    while(temp!='\0')
                    {
                        if (temp->category!=cat)
                        {
                            temp=temp->next;
                        }
                        else if (i!=num)
                        {
                            i++;
                            temp=temp->next;
                        }
                        else
                            break;
                    }
                }
                if(temp=='\0')
                    printf("da ghaby da wala eh\n");
                else
                    sell(temp);
            }
        }
        break;
    case 2:
        temp=end;
        while (temp!='\0')
        {
            if (z==1)
            {
                cat=temp->category;
            }
            if (cat==temp->category)
            {
                printf("%d-%s\n\t\t%f egp\t\t%d left in the machine\t\t#SN:%d\n\n",i,temp->name,temp->price,temp->quantity,temp->serial);
                i++;
            }
            temp=temp->prev;
        };
        if (w==1)
        {
            printf("\nwhich one do you want?\t\t\tpress 0 to go back\n");
            scanf("%d",&num);
            if (num==0)
                break;
            else
            {
                i=1;
                temp=end;
                if (z==1)
                {
                    while (temp!='\0'&&i!=num)
                    {
                        i++;
                        temp=temp->prev;
                    }
                }
                else
                {
                    while(temp!='\0')
                    {
                        if (temp->category!=cat)
                        {
                            temp=temp->prev;
                        }
                        else if (i!=num)
                        {
                            i++;
                            temp=temp->prev;
                        }
                        else
                            break;
                    }
                }
                if(temp=='\0')
                    printf("%d ezay ya sa7by\n",num);
                else
                    sell(temp);
            }
        }
        break;
    default :
        printf("\t\tERROR\n");
        break;
    }
}

void sell(struct node* ptr)
{
    int quan,money=0,x=0,j;
    float price,change,faka=0;
    char r;
    printf("you have chosen %s.\t\t%f egp\n\n",ptr->name,ptr->price);
label:
    printf("how much do you want? ");
    scanf("%d",&quan);
    price=(ptr->price)*quan;
    total=total+price;
    if((ptr->quantity)<quan)
    {
        printf("you don't have enough %s in the machine \(MAX=%d\)\n\n\n",ptr->name,ptr->quantity);
        goto label;
    }
    else
    {
        (ptr->quantity)=(ptr->quantity)-quan;
        for(j=0; j<i; j=j+2)
        {
            printf("%d X %s\t= %f egp\n",shopping[j+1],search_node_sn(shopping[j])->name,search_node_sn(shopping[j])->price*shopping[j+1]);
        }
        printf("%d X %s\t= %f egp\nTotal\t\t= %f egp\n\npress y to proceed to payment or s to continue shopping\n",quan,ptr->name,price,total);
        r=getch();
        if(r=='y'||r=='Y')
        {
            printf("press D to donate or any key to continue\n",change);
            r=getch();
            if(r=='d'||r=='D')
            {
                printf("how much do you want to donate ?");
                scanf("%f",&faka);
                donation=donation+faka;
                total=total+faka;
                printf("thanks for donating %f egp\n\nTotal\t\t= %f egp\n",faka,total);
            }
            while(money<total)
            {
                printf("please enter your money\n5egp\t10egp\t20egp\t50egp\t100egp\t200egp\n");
                scanf("%d",&x);
                if (x==0)
                {
                    printf("tab matgish tany ba2a\n");
                    break;
                }
                if(x==5||x==10||x==20||x==50||x==100||x==200)
                {
                    money=money+x;
                    if (money>=total)
                    {
                        change=money-total;
                        income=income+total-faka;
                        printf("\n\n\t\t\tReceit\n");
                        for(j=0; j<i; j=j+2)
                        {
                            printf("%d X %s\t= %f egp\n",shopping[j+1],search_node_sn(shopping[j])->name,search_node_sn(shopping[j])->price*shopping[j+1]);
                        }
                        printf("%d X %s\t= %f\ndonation\t= %f\nTotal\t\t= %f egp\npayment\t\t= %f egp\nchange due\t= %f egp\n\n\t\tTHANK YOU\n",quan,ptr->name,price,faka,total,(float)money,change);
                        save();
                    }
                    else
                        printf("you paid  %f egp\nremaining %f egp\n\n",(float)money,total-money);
                }
                else
                    printf("ya3m matet3ebnish ma3ak ma olna mesh 3ayzin faka\n\n");
            }
        }
        if(r=='s'||r=='S')
        {
            shopping[i]=ptr->serial;
            shopping[i+1]=quan;
            i=i+2;
            return;
        }

    }
    exit(0);
}

void add ()
{
    int serial,added_quan;
    printf("type the serial number: ");
    scanf("%d",&serial);
    struct node* temp;
    temp=search_node_sn(serial);
    if (temp=='\0')
    {
        printf("no product found with this serial.\n");
    }
    else
    {
        printf("%s\ntype the added quantity :",temp->name);
        scanf("%d",&added_quan);
        (temp->quantity)=(temp->quantity)+added_quan;

        printf("now you have %d in the machine.\n",temp->quantity);
    }
}

void edit()
{
    int x,serial;
    float price;
    char name[10];
    struct node* temp,*p1;
    printf("1-search by name.\n2-search by serial number.\n");
    scanf("%d",&x);
    switch(x)
    {
    case 1:
        printf("type the name : ");
        scanf("%s",&name);
        temp=search_node(name);
        break;
    case 2:
        printf("type the serial number : ");
        scanf("%d",&serial);
        temp=search_node_sn(serial);
        break;
    default :
        printf("\t\tERROR\n");
        break;
    }
    if (temp=='\0')
    {
        printf("no product found.\n");
    }
    else
    {
        printf("type the new price : ");
        scanf("%f",&price);
        p1=create_node(temp->name,price,temp->quantity,temp->serial,temp->category);
        delete_node(temp->name);
        insert_node(p1);
    }
}

void save()
{
    struct node* temp=start;
    int x,i=1;
    FILE *f;
    f=fopen("products.csv","w");
    fprintf(f,"donations ,%f\nincome ,%f\nname,serial,price,quantity,category\n",donation,income);
    while (temp!='\0')
    {
        fprintf(f,"%s ,%d ,%f ,%d ,%c\n",temp->name,temp->serial,temp->price,temp->quantity,temp->category);
        temp=temp->next;
    }
    fclose(f);
}

void export()
{
    struct node* temp=start;
    int x,i=1;
    FILE *f;
    char n[10];
    printf("export as:\n1-text file\n2-excel file\n");
    scanf("%d",&x);
    switch (x)
    {
    case 1:
    {
        printf("type the file name : ");
        scanf("%s",&n);
        strcat(n,".txt");
        f = fopen(n, "w");
        while (temp!='\0')
        {
            fprintf(f,"%d-name: %s\n  serial number: %d\n  price: %f\n  quantity: %d\n  category: %c\n\n",i,temp->name,temp->serial,temp->price,temp->quantity,temp->category);
            temp=temp->next;
            i++;
        }
        fclose(f);
        break;
    }
    case 2:
        printf("type the file name : ");
        scanf("%s",&n);
        strcat(n,".csv");
        f=fopen(n,"w");
        fprintf(f,"donations ,%f\nincome ,%f\nname,serial,price,quantity,category\n",donation,income);
        while (temp!='\0')
        {
            fprintf(f,"%s ,%d ,%f ,%d ,%c\n",temp->name,temp->serial,temp->price,temp->quantity,temp->category);
            temp=temp->next;
        }
        fclose(f);
        break;
    default :
        printf("\t\tERROR\n");
        break;
    }
    printf("done\n");
}

void read()
{
    struct node* ptr;
    FILE *f;
    char temp[10],name[10],cat;
    int serial,quantity;
    float price;
    f = fopen("products.csv", "r");
    fscanf(f,"%*s ,");
    fscanf(f,"%s",temp);
    donation=atof(temp);
    fscanf(f,"%*s ,");
    fscanf(f,"%s",temp);
    income=atof(temp);
    fscanf(f,"%*s");
    while (fscanf(f,"%s ,",temp)==1)
    {
        strcpy(name,temp);
        fscanf(f,"%s ,",temp);
        serial=atoi(temp);
        fscanf(f,"%s ,",temp);
        price=atof(temp);
        fscanf(f,"%s",temp);
        quantity=atoi(temp);
        fscanf(f,"%s",temp);
        cat=temp[1];
        ptr=create_node(name,price,quantity,serial,cat);
        insert_node(ptr);
    }
}

void open()
{
    struct node* ptr;
    FILE *f;
    char temp[10],name[10],n[10],cat;
    int serial,quantity;
    float price;
    printf("type the path of the excel file\n");
    scanf("%s",&n);
    f=fopen(n,"r");
    if (f=='\0')
        printf("not found\n");
    else
    {
        destroy_list();
        fscanf(f,"%*s ,");
        fscanf(f,"%s",temp);
        donation=atof(temp);
        fscanf(f,"%*s ,");
        fscanf(f,"%s",temp);
        income=atof(temp);
        fscanf(f,"%*s");
        while (fscanf(f,"%s ,",temp)==1)
        {
            strcpy(name,temp);
            fscanf(f,"%s ,",temp);
            serial=atoi(temp);
            fscanf(f,"%s ,",temp);
            price=atof(temp);
            fscanf(f,"%s",temp);
            quantity=atoi(temp);
            fscanf(f,"%s",temp);
            cat=temp[1];
            ptr=create_node(name,price,quantity,serial,cat);
            insert_node(ptr);
        }
        printf("done\n");
    }
}

void main()
{
    init_node();
    int x,z,quan,sn,i=0;
    float p;
    char n[10],cat,r;
    const char password[10]="ziadsaeed";
    struct node*p1;
    read();
repeat:
    printf("\t\t\tWELCOME\n\n");
    do
    {
        printf("1-menu\n2-search\n");
        scanf("%d", &x);
        printf("_________________________________________________________________________\n");
        switch(x)
        {
        case 0:
            break;
        case 1:
            if (start=='\0')
            {
                printf("the list is empty\n");
                system("pause");
            }
            else
            {
                print_list_price(1);
            }
            break;
        case 2:
            if (start=='\0')
            {
                printf("the list is empty\n");
                system("pause");
            }
            else
                search(1);
            break;
        case 12:
        {
            printf("password : ");
            do
            {
                n[i]=getch();
                if(n[i]!='\r')
                {
                    printf("*");
                }
                i++;
            }
            while(n[i-1]!='\r');
            n[i-1]='\0';
            if (strcmp(n,password)==0)
            {
                printf("\n\t\tconfirmed\n_________________________________________________________________________\n\t\t\tWELCOME\n");
                while(1)
                {
                    printf("\n1-add new product.\n2-add items\n3-delete a product\n4-clear the list\n5-print the list\n6-search\n7-income & donations\n8-edit price\n9-save the list\n10-export\n11-open file\n0-back\n");
                    scanf("%d",&z);
                    printf("_________________________________________________________________________\n\n");
                    switch(z)
                    {
                    case 0 :
                        system("cls");
                        goto repeat;
                        break;
                    case 1 :
                        printf("name : ");
                        scanf("%s",&n);
                        printf("serial number : ");
                        scanf("%d",&sn);
                        printf("price : ");
                        scanf("%f",&p);
                        printf("quantity : ");
                        scanf("%d",&quan);
                        printf("category :\ntype 's' for snacks\ntype 'b' for beverages\ntype 'c' for cigarettes\n");
                        scanf(" %c",&cat);
                        if(cat=='s'||cat=='b'||cat=='c')
                        {
                            p1=create_node(n,p,quan,sn,cat);
                            insert_node(p1);
                        }
                        else
                            printf("you must type 's' , 'b' or 'c' in lower case\n");
                        break;
                    case 2:
                        add();
                        break;
                    case 3 :
                        if (start=='\0')
                        {
                            printf("the list is empty\n");
                        }
                        else
                        {
                            printf("type the serial number: ");
                            scanf("%d",&sn);
                            delete_node(sn);
                        }
                        break;
                    case 4 :
                        if (start=='\0')
                        {
                            printf("the list is already empty\n");
                        }
                        else
                        {
                            printf("are you sure you want to clear the list\n\t\tpress y to delete or any key to cancel\n");
                            r=getch();
                            if(r=='y'||r=='Y')
                            {
                                destroy_list();
                                printf("the list is cleared successfully\n");
                            }
                        }
                        break;

                    case 5 :
                        if (start=='\0')
                        {
                            printf("no products found\n");
                        }
                        else
                        {
                            print_list_price(0);
                            system("pause");
                        }
                        break;
                    case 6 :
                        if (start=='\0')
                        {
                            printf("the list is empty\n");
                        }
                        else
                        {
                            search(0);
                            system("pause");
                        }
                        break;
                    case 7:
                        printf("\n\tDONATIONS = %f egp\n\n\tINCOME = %f egp\n\n",donation,income);
                        printf("\t\tpress y to clear all or any key to cancel\n");
                        r=getch();
                        if(r=='y'||r=='Y')
                        {
                            donation=income=0;
                            printf("\n\tDONATIONS = %f egp\n\n\tINCOME = %f egp\n\n",donation,income);
                            system("pause");
                        }
                        ;
                        break;
                    case 8:
                        if (start=='\0')
                        {
                            printf("the list is empty.\n");
                        }
                        else
                            edit();
                        break;
                    case 9:
                        save();
                        printf("\t\tsaved successfully\n");
                        break;
                    case 10 :
                        if (start=='\0')
                        {
                            printf("the list is empty\n");
                        }
                        else
                            export();
                        break;
                    case 11 :
                        open();
                        break;
                    default:
                        printf("\t\tERROR\n");
                    }
                    printf("_________________________________________________________________________\n");
                }
            }
            else
                printf("\n\t\twrong :D\n");
            break;
        }
        default :
            printf("\t\tERROR\n");
            break;
        }
        printf("_________________________________________________________________________\n");
    }
    while(x);
}
