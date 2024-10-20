//220201032 berk güven
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <SDL.h>

//size_t bir tamsayı türüdür ve çeşitli durumlarda boyutları temsil etmek için kullanılabilir
size_t write_data(void *veripointeri, size_t elemanboyutu, size_t elemansayisi, void *dondurulenpointer)
{
    // Verinin toplam boyutunu hesaplama
    size_t veriboyutu = elemanboyutu * elemansayisi;
    // Veriyi bellek alanına kopyalama
    memcpy(dondurulenpointer, veripointeri, veriboyutu);

    // return, libcurl'ün veriyi doğru bir şekilde işlemesine yardımcı olur.
    return veriboyutu;
}


int main(int argc, char *argv[])
{
    kordinatlar();

    return 0;
}


int kordinatlar()
{
    // *curl pointerı libcurl kütüphanesini kullanarak web istekleri yapar ve yanıtları alır.
    CURL *curl;
    // Veri değişkeni, urlden gelen yanıtları tutar
    CURLcode veri;
    // easy_init fonksiyonu bir CURL işaretçisi oluşturur ve başlatır
    curl = curl_easy_init();

    // Veriyi saklayacağımız yer
    char *depo[1000];

    if(curl)
    {
        // Veriyi saklayacağımız yer olan depo'yu belirtir
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, depo);

        // Veriyi saklamak için kullanılacak yazma işlevi
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

        // Bu satır curl'e bir URL belirtmemizi sağlar
        curl_easy_setopt(curl, CURLOPT_URL, "http://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt");

        /* easy_perform fonksiyonu curl pointerı ile belirtilen URL'ye bir HTTP GET isteği gönderir
        HTTP GET isteği, belirtilen URL'den veri almak için kullanılır */
        veri = curl_easy_perform(curl);


        char *ptr = depo;
        printf("KORDINATLARIMIZ\n%s\n\n",ptr);

        int x[100], y[100];
        int sayac = 0;
        char dizi[100];
        int i=0;


        printf("Cizimi yapilacak satiri seciniz (1 ya da 2): ");
        int satirnumarasi;
        scanf("%d", &satirnumarasi);
        char *satir;


        if(satirnumarasi==1)
        {
            satir = strtok(ptr, "\n");
        }

        else if(satirnumarasi==2)
        {
            satir = strtok(ptr, "\n");
            satir = strtok(NULL, "\n");
        }
        else
        {
            printf("Hatali deger girdiniz!");
            return 0;
        }
        strcpy(dizi, satir);


        int ayrac;
        if(satirnumarasi==1)
        {
            int x1[100], y1[100];
            int x2[100], y2[100];

            for(i = 0; dizi[i] != '\0'; i++)
            {
                if(dizi[i] == '(')
                {
                    if(sscanf(dizi + i, "(%d,%d)", &x[sayac], &y[sayac]) == 2)
                    {
                        sayac++;
                        x[sayac]=NULL;
                        y[sayac]=NULL;
                    }
                }
            }

            int yenidevam=0;
            for(i = 0; i < sayac; i++)
            {
                x1[i]=x[i];
                y1[i]=y[i];
                if(i!=0 && x[0]==x[i] && y[0]==y[i])
                {
                    i++;
                    ayrac=i;
                    x1[i]=NULL;
                    y1[i]=NULL;
                    if(x[i]!=NULL && y[i]!=NULL)
                        yenidevam=1;
                    break;
                }
            }


            while(yenidevam==1)
            {
                int j=0;
                while(i<sayac)
                {

                    x2[j]=x[i];
                    y2[j]=y[i];
                    i++;
                    j++;
                    if(i==sayac)
                    {
                        x2[j]=NULL;
                        y2[j]=NULL;
                        yenidevam=2;

                    }

                }
            }

            if(yenidevam==0)
            {
                int alan = alanhesapla(sayac,x1,y1)*10;
                printf("Kaynak rezerv degeri: %d",alan);
                asama1(x1,y1,x1,y1,1);
                asama2(x1,y1,x1,y1,1,alan);
            }
            else if(yenidevam==2)
            {
                int alan1 = alanhesapla(ayrac,x1,y1);
                int alan2 = alanhesapla(sayac-ayrac,x2,y2);
                int alan = (alan1 + alan2)*10;
                printf("Kaynak rezerv degeri: %d",alan);
                asama1(x1,y1,x2,y2,2);
                asama2(x1,y1,x2,y2,2,alan);
            }


        }

        else if(satirnumarasi==2)
        {
            int x1[100], y1[100];
            int x2[100], y2[100];

            for(i = 0; dizi[i] != '\0'; i++)
            {
                if(dizi[i] == '(')
                {
                    if(sscanf(dizi + i, "(%d,%d)", &x[sayac], &y[sayac]) == 2)
                    {
                        sayac++;
                        x[sayac]=NULL;
                        y[sayac]=NULL;
                    }
                }
            }

            int yenidevam=0;
            for(i = 0; i < sayac; i++)
            {
                x1[i]=x[i];
                y1[i]=y[i];
                if(i!=0 && x[0]==x[i] && y[0]==y[i])
                {

                    i++;
                    ayrac=i;
                    x1[i]=NULL;
                    y1[i]=NULL;
                    if(x[i]!=NULL && y[i]!=NULL)
                        yenidevam=1;
                    break;
                }
            }

            while(yenidevam==1)
            {
                int j=0;
                while(i<sayac)
                {

                    x2[j]=x[i];
                    y2[j]=y[i];
                    i++;
                    j++;
                    if(i==sayac)
                    {
                        x2[j]=NULL;
                        y2[j]=NULL;
                        yenidevam=2;
                    }

                }
            }


            if(yenidevam==0)
            {
                int alan = alanhesapla(sayac,x1,y1)*10;
                printf("Kaynak rezerv degeri: %d",alan);
                asama1(x1,y1,x1,y1,1);
                asama2(x1,y1,x1,y1,1,alan);
            }
            else if(yenidevam==2)
            {
                int alan1 = alanhesapla(ayrac,x1,y1);
                int alan2 = alanhesapla(sayac-ayrac,x2,y2);
                int alan = (alan1 + alan2)*10;
                printf("Kaynak rezerv degeri: %d",alan);
                asama1(x1,y1,x2,y2,2);
                asama2(x1,y1,x2,y2,2,alan);
            }

        }

        curl_easy_cleanup(curl);
    }
}


void asama1(int x1[],int y1[], int x2[], int y2[],int a)
{
    // SDL baþlatma
    SDL_Init(SDL_INIT_VIDEO);

    // Pencere oluþturma
    SDL_Window *window = SDL_CreateWindow("Proje1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_SHOWN);

    // Çizim yüzeyi oluþturma
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    // Olay döngüsü
    int devam = 1;
    SDL_Event event;
    while (devam)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                devam = 0;

            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    devam = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        int i=0,t=0,birim=0;
        int x,y,k,z;
        if(a==1)
        {
            for(i = 0; x1[i+1]!=NULL && y1[i+1]!=NULL; i++)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x1[i]*10, y1[i]*10, x1[i+1]*10, y1[i+1]*10);

                if(x1[i]<x1[i+1] && y1[i+1]<y1[i])
                {
                    k=1;
                }
                else if(x1[i]<x1[i+1] && y1[i]<y1[i+1])
                {
                    k=2;
                }
                else if(x1[i+1]<x1[i] && y1[i]<y1[i+1])
                {
                    k=3;
                }
                else if(x1[i+1]<x1[i] && y1[i+1]<y1[i])
                {
                    k=4;
                }


                if(k==1)
                {
                    if((y1[i]-y1[i+1])>=(x1[i+1]-x1[i])*2-2)
                    {
                        t=0;
                        z=x1[i]*10-10;
                        for (y = ((y1[i]*10)-10); y>=y1[i+1]*10; y-=10)
                        {
                            for (x=z; x<=x1[i+1]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim++;
                            }
                            if(t%2==1)
                                z=z+10;
                            t++;

                        }

                    }
                    else
                    {
                        z=x1[i]*10-10;
                        for (y = ((y1[i]*10)-10); y>=y1[i+1]*10; y-=10)
                        {
                            for (x=z; x<=x1[i+1]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim++;
                            }
                            z=z+10;
                        }
                    }

                }
                else if(k==2)
                {
                    if((y1[i+1]-y1[i])>=(x1[i+1]-x1[i])*2-2)
                    {
                        t=0;
                        z=x1[i+1]*10-10;
                        for (y = y1[i+1]*10-10; y>=y1[i]*10; y-=10)
                        {
                            for (x=z ;x>=x1[i]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z-10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x1[i+1]*10-10;
                        for (y = y1[i+1]*10-10; y>=y1[i]*10; y-=10)
                        {
                            for (x=z ;x>=x1[i]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z-10;
                        }
                    }


                }
                else if(k==3)
                {
                    if((y1[i+1]-y1[i])>=(x1[i]-x1[i+1])*2-2)
                    {
                        t=0;
                        z=x1[i]*10-10;
                        for (y = y1[i]*10; y<=y1[i+1]*10; y+=10)
                        {
                            for (x=z ;x>=x1[i+1]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z-10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x1[i]*10-10;
                        for (y = y1[i]*10; y<=y1[i+1]*10; y+=10)
                        {
                            for (x=z ;x>=x1[i+1]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z-10;
                        }
                    }


                }
                else if(k==4)
                {
                    if((y1[i]-y1[i+1])>=(x1[i]-x1[i+1])*2-2)
                    {
                        t=0;
                        z=x1[i+1]*10-10;
                        for (y = y1[i+1]*10; y<=y1[i]*10-10; y+=10)
                        {
                            for (x=z ;x<=x1[i]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z+10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x1[i+1]*10;
                        for (y = y1[i+1]*10; y<=y1[i]*10-10; y+=10)
                        {
                            for (x=z ;x<=x1[i]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z+10;
                        }
                    }
                }


            }
        }


        else if(a==2)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for(i = 0; x1[i+1]!=NULL && y1[i+1]!=NULL; i++)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x1[i]*10, y1[i]*10, x1[i+1]*10, y1[i+1]*10);

                if(x1[i]<x1[i+1] && y1[i+1]<y1[i])
                {
                    k=1;
                }
                else if(x1[i]<x1[i+1] && y1[i]<y1[i+1])
                {
                    k=2;
                }
                else if(x1[i+1]<x1[i] && y1[i]<y1[i+1])
                {
                    k=3;
                }
                else if(x1[i+1]<x1[i] && y1[i+1]<y1[i])
                {
                    k=4;
                }


                if(k==1)
                {
                    if((y1[i]-y1[i+1])>=(x1[i]-x1[i+1])*2-2)
                    {
                        t=0;
                        z=x1[i]*10;
                        for (y = ((y1[i]*10)-10); y>=y1[i+1]*10; y-=10)
                        {
                            for (x=z; x<=x1[i+1]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z+10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x1[i]*10;
                        for (y = ((y1[i]*10)-10); y>=y1[i+1]*10; y-=10)
                        {
                            for (x=z; x<=x1[i+1]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z+10;
                        }
                    }


                }


                else if(k==2)
                {
                    if((y1[i+1]-y1[i])>=(x1[i+1]-x1[i])*2-2)
                    {
                        t=0;
                        z=x1[i+1]*10-10;
                        for (y = y1[i+1]*10-10; y>=y1[i]*10; y-=10)
                        {
                            for (x=z ;x>=x1[i]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z-10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x1[i+1]*10-10;
                        for (y = y1[i+1]*10-10; y>=y1[i]*10; y-=10)
                        {
                            for (x=z ;x>=x1[i]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z-10;
                        }
                    }


                }


                else if(k==3)
                {
                    if((y1[i+1]-y1[i])>=(x1[i]-x1[i+1])*2-2)
                    {
                        t=0;
                        z=x1[i]*10-10;
                        for (y = y1[i]*10; y<y1[i+1]*10; y+=10)
                        {
                            for (x=z ;x>=x1[i+1]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z-10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x1[i]*10-10;
                        for (y = y1[i]*10; y<y1[i+1]*10; y+=10)
                        {
                            for (x=z ;x>=x1[i+1]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z-10;
                        }

                    }
                }


                else if(k==4)
                {
                    if((y1[i]-y1[i+1])>=(x1[i]-x1[i+1])*2-2)
                    {
                        t=0;
                        z=x1[i+1]*10-10;
                        for (y = y1[i+1]*10; y<=y1[i]*10-10; y+=10)
                        {
                            for (x=z ;x<=x1[i]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z+10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x1[i+1]*10-10;
                        for (y = y1[i+1]*10; y<=y1[i]*10-10; y+=10)
                        {
                            for (x=z ;x<=x1[i]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z+10;
                        }
                    }
                }
            }


            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            for(i = 0; x2[i+1]!=NULL && y2[i+1]!=NULL; i++)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x2[i]*10, y2[i]*10, x2[i+1]*10, y2[i+1]*10);

                if(x2[i]<x2[i+1] && y2[i+1]<y2[i])
                {
                    k=1;
                }
                else if(x2[i]<x2[i+1] && y2[i]<y2[i+1])
                {
                    k=2;
                }
                else if(x2[i+1]<x2[i] && y2[i]<y2[i+1])
                {
                    k=5;
                }
                else if(x2[i+1]<x2[i] && y2[i+1]<y2[i])
                {
                    k=4;
                }


                if(k==1)
                {
                    if((y2[i]-y2[i+1])>=(x2[i+1]-x2[i])*2-2)
                    {
                        t=0;
                        z=x2[i]*10;
                        for (y = ((y2[i]*10)-10); y>=y2[i+1]*10; y-=10)
                        {
                            for (x=z; x<=x2[i+1]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z+10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x2[i]*10;
                        for (y = ((y2[i]*10)-10); y>=y2[i+1]*10; y-=10)
                        {
                            for (x=z; x<=x2[i+1]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z+10;
                        }
                    }


                }
                else if(k==2)
                {
                    if((y2[i+1]-y2[i])>=(x2[i+1]-x2[i])*2-2)
                    {
                        t=0;
                        z=x2[i+1]*10-10;
                        for (y = y2[i+1]*10-10; y>=y2[i]*10; y-=10)
                        {
                            for (x=z ;x>=x2[i]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z-10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x2[i+1]*10-10;
                        for (y = y2[i+1]*10-10; y>=y2[i]*10; y-=10)
                        {
                            for (x=z ;x>=x2[i]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z-10;
                        }
                    }


                }
                else if(k==3)
                {
                    if((y2[i+1]-y2[i])>=(x2[i]-x2[i+1])*2-2)
                    {
                        t=0;
                        z=x2[i]*10-10;
                        for (y = y2[i]*10; y<=y2[i+1]*10; y+=10)
                        {
                            for (x=z ;x>=x2[i+1]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z-10;
                            t++;
                        }
                    }
                    else
                    {
                        z=x2[i]*10-10;
                        for (y = y2[i]*10; y<=y2[i+1]*10; y+=10)
                        {
                            for (x=z ;x>=x2[i+1]*10; x-=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z-10;
                        }
                    }


                }
                else if(k==4)
                {
                    if((y2[i]-y2[i+1])>=(x2[i]-x2[i+1])*2-2)
                    {
                        t=0;
                        z=x2[i+1]*10-10;
                        for (y = y2[i+1]*10; y<=y2[i]*10-10; y+=10)
                        {
                            for (x=z ;x<=x2[i]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            if(t%2==1)
                                z=z+10;
                            t++;
                        }

                    }
                    else
                    {
                        z=x2[i+1]*10-10;
                        for (y = y2[i+1]*10; y<=y2[i]*10-10; y+=10)
                        {
                            for (x=z ;x<=x2[i]*10; x+=10)
                            {
                                SDL_Rect kare = {x,y,10,10};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                            }
                            z=z+10;
                        }
                    }


                }


            }

        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

        for (x = 0; x < 1000; x += 50)
            {
            for (y = 0; y < 800; y += 50)
            {
                SDL_Rect rect = {x, y, 1, 1};
                SDL_RenderDrawRect(renderer, &rect);
            }
        }

        // Çizim yüzeyini güncelle
        SDL_RenderPresent(renderer);
    }


    // Belleği temizle ve SDL'yi kapat
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}


int alanhesapla(int n, int x[], int y[])
{
    int alan=0;

    for (int i=0; i<n-1; i++)
    {
        alan+=(x[i]*y[i + 1])-(x[i + 1]*y[i]);
    }

    if(alan<0)
        alan=alan*(-1);
    if(n!=4) //üçgende geçersiz
        alan=alan/2;

    return alan;
}


void asama2(int x1[],int y1[], int x2[], int y2[],int a,int rezerv)
{
    int sondaj,platform,sondajmaliyeti,platformmaliyeti,toplammaliyet;
    printf("\n\nSondaj maliyetini giriniz (1 ile 10 arasi): ");
    scanf("%d",&sondaj);
    if(sondaj<1 || sondaj>10)
    {
        printf("Gecersiz deger girdiniz!");
        return -1;
    }
    printf("Platform maliyetini giriniz: ");
    scanf("%d",&platform);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("Proje1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int birim,adet;
    int birim2,adet2;
    // Olay döngüsü
    int devam = 1;
    SDL_Event event;
    while (devam)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                devam = 0;
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    devam = 0;
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);


        int i,x,y;
        birim=0,adet=0;
        birim2=0,adet2=0;

        if(a==1)
        {
            for(i = 0; x1[i+1]!=NULL && y1[i+1]!=NULL; i++)
            {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
                SDL_RenderDrawLine(renderer, x1[i]*10, y1[i]*10, x1[i+1]*10, y1[i+1]*10);

                int xmin=x1[0],ymin=y1[0],xmax=x1[0],ymax=y1[0];
                for(int i=0; x1[i+1]!=NULL && y1[i+1]!=NULL; i++)
                {
                    if(xmin>x1[i])
                        xmin=x1[i];
                    if(xmax<x1[i])
                        xmax=x1[i];
                    if(ymin>y1[i])
                        ymin=y1[i];
                    if(ymax<y1[i])
                        ymax=y1[i];
                }

                if(sondaj>=7)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if(i==8 && j==4)
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+16;
                                adet++;
                            }

                            if(i+j==9||(j==1&&(i==9||i==10))||(j==3&&i==12)||(j==5&&(i==5||i==14))||(j==6&&i==5)||(j==3&&i==7))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+1;
                                adet++;
                            }
                            if((j==7&&i==16)||(j==8&&(i==7||i==16))||(j==10&&(i==9||i==14))||(j==12&&(i==11||i==12)))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+1;
                                adet++;
                            }

                            if((j==2&&(i==8||i==10))||(j==4&&(i==6||i==12))||(j==6&&(i==6||i==12||i==14)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                            if((j==8&&(i==8||i==10||i==12||i==14))||(j==10&&(i==10||i==12)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }

                        }
                    }
                }

                else if(sondaj>3 && sondaj<7)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if((i==8 && j==4)||(j==6 && i==12))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+16;
                                adet++;
                            }

                            if(i+j==9||(j==1&&(i==9||i==10))||(j==3&&i==12)||(j==5&&i==5)||(j==6&&i==5)||(j==3&&i==7))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+1;
                                adet++;
                            }
                            if((j==8&&i==7)||(j==10&&i==9)||(j==12&&(i==11||i==12)))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+1;
                                adet++;
                            }

                            if((j==7&&i==16)||(j==2&&(i==8||i==10))||(j==4&&(i==6||i==12))||(j==6&&i==6))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                            if((j==8&&(i==8||i==10))||(j==10&&(i==10||i==12))||(j==4&&i==14)||(j==10&&i==14))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }

                        }
                    }
                }
                else if(sondaj<=3)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if((i==8&&j==4)||(j==4&&i==12)||(j==8&&i==12)||(j==8&&i==8))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+16;
                                adet++;
                            }

                            if(i+j==9||(j==1&&(i==9||i==10))||(j==5&&i==5||(j==6&&i==5)||(j==3&&i==7)))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+1;
                                adet++;
                            }

                            if((j==7&&i==16)||(j==2&&(i==8||i==10||i==12))||(j==4&&i==6))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                            if((j==6&&i==6)||(j==8&&i==6)||(j==12&&i==11))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }

                        }
                    }
                }

            }
            birim=birim/4;
            adet=adet/4;
            sondajmaliyeti=birim*sondaj;
            platformmaliyeti=adet*platform;
            toplammaliyet=platformmaliyeti+sondajmaliyeti;
        }


        else if(a==2)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for(i = 0; x1[i+1]!=NULL && y1[i+1]!=NULL; i++)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x1[i]*10, y1[i]*10, x1[i+1]*10, y1[i+1]*10);

                int xmin=x1[0],ymin=y1[0],xmax=x1[0],ymax=y1[0];
                for(int i=0; x1[i+1]!=NULL && y1[i+1]!=NULL; i++)
                {
                    if(xmin>x1[i])
                        xmin=x1[i];
                    if(xmax<x1[i])
                        xmax=x1[i];
                    if(ymin>y1[i])
                        ymin=y1[i];
                    if(ymax<y1[i])
                        ymax=y1[i];
                }

                if(sondaj>=7)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if((j==12&&i==32)||(j==16&&(i==26||i==30||i==34))||(j==20&&(i==22||i==26||i==30))||(j==24&&i==24))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+16;
                                adet++;
                            }
                            if((j==10&&(i==38||i==39))||(j==11&&(i==36||i==37)))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+1;
                                adet++;
                            }
                            if((j==29&&(i==20||i==21))||(j==28&&(i==22||i==23)))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+1;
                                adet++;
                            }
                            if((i==38&&(j==11||j==13||j==15||j==17||j==19))||(i==36&&(j==12||j==14)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                            if((i==20&&(j==19||j==21||j==23||j==25||j==27))||(i==22&&(j==24||j==26)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                            if((j==14&&(i==28||i==30))||(j==24&&(i==28||i==30))||(j==22&&i==34))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                            if((j==18&&(i==22||i==24))||(j==20&&(i==34||i==36))||(j==16&&i==24))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                        }
                    }
                }
                else if(sondaj>3 && sondaj<7)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if(j==16 && i==26)
                            {
                                SDL_Rect kare = {j*10,i*10,80,80};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+64;
                                adet++;
                            }
                            if((j==12&&(i==28||i==32))||(j==16&&(i==22||i==34)))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+16;
                                adet++;
                            }
                            if((j==20&&(i==22||i==34))||(j==24&&(i==24||i==28)))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+16;
                                adet++;
                            }
                            if((i==38&&(j==11||j==13||j==15||j==17||j==19))||(i==36&&(j==12||j==14)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                            if((i==20&&(j==19||j==21||j==23||j==25||j==27))||(i==22&&(j==24||j==26)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+4;
                                adet++;
                            }
                            if((j==10&&(i==38||i==39))||(j==11&&(i==36||i==37))||(j==28&&(i==22||i==23))||(j==29&&(i==20||i==21)))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+1;
                                adet++;
                            }
                        }
                    }
                }
                else if(sondaj<=3)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if((j==18&&i==20)||(j==14&&i==32))
                            {
                                SDL_Rect kare = {j*10,i*10,80,80};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+64;
                                adet++;
                            }
                            if((j==10&&(i==32||i==36))||(j==14&&(i==24||i==28))||(j==26&&(i==20||i==24)))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+16;
                                adet++;
                            }
                            if((j==22&&(i==28||i==32))||(j==18&&i==28))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim=birim+16;
                                adet++;
                            }

                        }
                    }
                }

            }

            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            for(i = 0; x2[i+1]!=NULL && y2[i+1]!=NULL; i++)
            {
                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                SDL_RenderDrawLine(renderer, x2[i]*10, y2[i]*10, x2[i+1]*10, y2[i+1]*10);

                int xmin=x2[0],ymin=y2[0],xmax=x2[0],ymax=y2[0];
                for(int i=0; x2[i+1]!=NULL && y2[i+1]!=NULL; i++)
                {
                    if(xmin>x2[i])
                        xmin=x2[i];
                    if(xmax<x2[i])
                        xmax=x2[i];
                    if(ymin>y2[i])
                        ymin=y2[i];
                    if(ymax<y2[i])
                        ymax=y2[i];
                }

                if(sondaj>=7)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if((j==38&&i==26))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+16;
                                adet2++;
                            }
                            if((j==31&&(i==30||i==31))||(j==33&&(i==28||i==29))||(j==35&&(i==26||i==27))||(j==37&&(i==24||i==25)))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+1;
                                adet2++;
                            }
                            if((j==42&&(i==24||i==25))||(j==44&&(i==26||i==27))||(j==46&&(i==28||i==29)))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+1;
                                adet2++;
                            }
                            if((i==31&&(j==30||j==49))||(i==29&&(j==32||j==47))||(i==27&&(j==34||j==45))||(j==41&&i==23))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+1;
                                adet2++;
                            }
                            if((i==25&&(j==36||j==43))||(j==48&&(i==30||i==31))||(j==48&&(i==30||i==31))||(j==38&&i==23))
                            {
                                SDL_Rect kare = {j*10,i*10,10,10};
                                SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+1;
                                adet2++;
                            }
                            if((i==30&&(j==32||j==34||j==36||j==38||j==40||j==42||j==44||j==46))||(j==39&&i==22))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+4;
                                adet2++;
                            }
                            if((i==28&&(j==34||j==36||j==42||j==44))||(i==26&&(j==36||j==42))||(i==24&&(j==38||j==40)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+4;
                                adet2++;
                            }
                        }
                    }
                }
                else if(sondaj>3 && sondaj<7)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if((j==38&&(i==24||i==28))||(i==28&&(j==34||j==42)))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+16;
                                adet2=adet2+1;
                            }
                            if((i==30&&(j==30||j==32||j==46||j==48))||(i==28&&(j==32||j==46))||(i==26&&(j==34||j==36)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+4;
                                adet2=adet2+1;
                            }
                            if((i==26&&(j==42||j==44))||(i==24&&(j==36||j==42))||(i==22&&(j==38||j==40)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+4;
                                adet2=adet2+1;
                            }
                        }
                    }
                }
                else if(sondaj<=3)
                {
                    for(int i=ymin; i<ymax; i++)
                    {
                        for(int j=xmin; j<xmax; j++)
                        {
                            if((i==28&&(j==32||j==36||j==40||j==44))||(i==24&&(j==36||j==40)))
                            {
                                SDL_Rect kare = {j*10,i*10,40,40};
                                SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+16;
                                adet2++;
                            }
                            if((i==30&&(j==30||j==48))||(i==26&&(j==34||j==44))||(i==22&&(j==38||j==40)))
                            {
                                SDL_Rect kare = {j*10,i*10,20,20};
                                SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                                SDL_RenderDrawRect(renderer, &kare);
                                birim2=birim2+4;
                                adet2++;
                            }
                        }
                    }
                }


            }

            birim=birim/4;
            birim2=birim2/3;
            adet=adet/4;
            adet2=adet2/3;
            sondajmaliyeti=birim*sondaj+birim2*sondaj;
            platformmaliyeti=adet*platform+adet2*platform;
            toplammaliyet=platformmaliyeti+sondajmaliyeti;
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 1);

        for (x = 0; x < 1000; x += 50)
            {
            for (y = 0; y < 800; y += 50)
            {
                SDL_Rect rect = {x, y, 1, 1};
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
        // Çizim yüzeyini güncelle
        SDL_RenderPresent(renderer);
    }


    // SDL'i kapatır belleği temizler
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    if(a==1)
    {
        printf("\nToplam platform sayisi: %d\n",adet);
        printf("Toplam sondaj sayisi: %d\n\n",birim);
        printf("Toplam platform maliyeti: %d\n",platformmaliyeti);
        printf("Toplam sondaj maliyeti: %d\n\n",sondajmaliyeti);
        printf("Toplam maliyet: %d\n",toplammaliyet);
        printf("Toplam kar miktari: %d\n",rezerv-toplammaliyet);
    }
    if(a==2)
    {
        printf("\nToplam platform sayisi: %d\n",adet2+adet);
        printf("Toplam sondaj sayisi: %d\n\n",birim2+birim);
        printf("Toplam platform maliyeti: %d\n",platformmaliyeti);
        printf("Toplam sondaj maliyeti: %d\n\n",sondajmaliyeti);
        printf("Toplam maliyet: %d\n",toplammaliyet);
        printf("Toplam kar miktari: %d\n",rezerv-toplammaliyet);
    }

}
