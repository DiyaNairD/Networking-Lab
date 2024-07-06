#include<stdio.h>

void main()
{
    int bucket_size,n,outgoing,incoming,store=0;
    printf("enter the bucket size,outgoing raite and no.of inputs:\n");
    scanf("%d%d%d",&bucket_size,&outgoing,&n);

    while(n!=0)
    {
        printf("enter the size of incoming packet:\n");
        scanf("%d",&incoming);

        if(incoming<(bucket_size-store))
        {
            store = store + incoming;
        }
        else
        {
            store = bucket_size;
            printf("dropped %d no.of packets from\n",incoming-(bucket_size-store));
        }
        printf("bucket buffer size %d out of %d\n",store,bucket_size);
        store=store-outgoing;
        if(store<0)
            store=0;
        printf("after outgoing %d packets are left in buffer out of %d\n",store,bucket_size);
        n--;
    }
}