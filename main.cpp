/*Projeto Biodiesel

 Desenvolvido por: Gabriel Spinardi - 22.215.065-8
                   Lucas Eduardo da Silva Bispo - 22.216.010-3

*/
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <Windows.h>
#include <thread>

float qtd_oleo 					= 0;
float qtd_naoh 					= 0;
float qtd_etoh 					= 0;
float qtd_glicerina 			= 0;
float qtd_lavagem				= 0;
float qtd_mistura				= 0;
float qtd_etoh_decantador       = 0;
float qtd_total_mistura 		= 0;
float qtd_total_lavagem 		= 0;
float qtd_mistura_decantador	= 0;
float qtd_biodiesel_total 		= 0;
int ativa_reator            	= 0;
int tempo2                      = clock();
int tempo_oleo                  = 1;
int tempo_dec                   = 1;
float qtd_total_oleo_reator 	= 0;
float qtd_total_naoh_reator 	= 0;
float qtd_total_etoh_reator 	= 0;
float qtd_total_glicerina   	= 0;
float qtd_total_decantador  	= 0;
float qtd_total_naoh 			= 0;
float qtd_total_etoh 			= 0;
float qtd_total_oleo            = 0;




void tanque_biodiesel(float qtd_biodiesel) //Gabriel
{
    printf("\n\nTANQUE DE BIODIESEL:");
    qtd_biodiesel_total = qtd_biodiesel_total + qtd_biodiesel;
    printf("\n Quantidade de Biodiesel no Tanque: %.3f.", qtd_biodiesel_total);
    printf("\n\n");

}


void secador(float qtd_mistura_decantador) //Lucas
{
    printf("\n\nSECADOR:");


    if(qtd_naoh == 0 && qtd_etoh == 0 )
    {
        printf("\nO secador ainda nao recebeu a mistura.");
    }
    else
    {
        printf("\nRecebendo %.3f de mistura do tanque de lavagem.", qtd_mistura_decantador);
        qtd_mistura_decantador = qtd_mistura_decantador - (qtd_mistura_decantador * 0.03);
        printf("\nApos perder 3 por cento do volume, restaram %.3f de mistura no secador.", qtd_mistura_decantador);

        std::thread TQ_BIO(tanque_biodiesel, qtd_mistura_decantador);
        TQ_BIO.join();
    }
    printf("\n");

}

void tanque_glicerina(float qtd_glicerina) //Gabriel
{
    printf("\n\n TANQUE DE GLICERINA:");
    qtd_total_glicerina = qtd_total_glicerina + qtd_glicerina;

    printf("\nQuantidade de glicerina: %.3f.", qtd_total_glicerina);
    printf("\n");
}




void tanque_lavagem(float qtd_mistura_decantador) //Gabriel
{

    printf("\nTANQUE DE LAVAGEM:");
    printf("\nRecebendo %.3f de solucao para lavagem.... ", qtd_mistura_decantador);
    qtd_mistura_decantador = qtd_mistura_decantador - (qtd_mistura_decantador * 0.075);
    printf("\nApos perder 7.5 por cento da solucao, a quantidade para lavagem restante e de %.3f", qtd_mistura_decantador);

    std::thread SECADOR(secador, qtd_mistura_decantador);
    SECADOR.join();
    printf("\n");
}

void decantador(float qtd_mistura) //Lucas
{
    printf("\n\nDECANTADOR:");
    qtd_total_decantador = qtd_total_decantador + qtd_mistura;

    if(tempo_dec == 5 )
    {
        if( qtd_total_decantador >= 3 )
        {
            qtd_glicerina = qtd_total_decantador * 0.02;
            qtd_etoh_decantador = qtd_total_decantador * 0.09;
            qtd_lavagem = qtd_total_decantador * 0.89;
            qtd_mistura_decantador = qtd_glicerina + qtd_etoh + qtd_lavagem;

            qtd_total_decantador = qtd_total_decantador - 3.0;
            printf("\nDecantador processou 3L.");
            printf("\nQuantidade de mistura no decantador: %.3fL.", qtd_total_decantador);
            tempo_dec = 1;
            printf("\n");

            std::thread TQ_GLI(tanque_glicerina, qtd_glicerina);
            TQ_GLI.join();


            std::thread TQ_LAV(tanque_lavagem, qtd_mistura_decantador);
            TQ_LAV.join();

        }
        else
        {
            printf("\n MISTURA INSUFICIENTE PARA PROCESSAMENTO. ");
            printf("\n Quantidade de mistura disponivel: %.3fL.", qtd_total_decantador);
            printf("\n");
        }
    }
    else
    {
        printf("\nDecantador ainda nao foi ativado.");
        printf("\n");
        tempo_dec++;
    }
}

void reator(float qtd_oleo, float qtd_naoh, float qtd_etoh) //Lucas
{


    printf("\n\nREATOR:\n");
    printf("\nRecebendo %.3fL de Hidroxido de Sodio.", qtd_naoh);
    printf("\nRecebendo %.3fL de Etanol.", qtd_etoh);
    printf("\nRecebendo %.3fL de Oleo.", qtd_oleo);
    qtd_total_naoh_reator = qtd_total_naoh_reator + qtd_naoh;
    qtd_total_etoh_reator = qtd_total_etoh_reator + qtd_etoh;
    qtd_total_oleo_reator = qtd_total_oleo_reator + qtd_oleo;
    printf("\nQuantidade total de hidroxido de sodio no reator: %.3fL.", qtd_total_naoh_reator);
    printf("\nQuantidade total de etanol no reator: %.3fL.", qtd_total_etoh_reator);
    printf("\nQuantidade total de oleo no reator: %.3fL.", qtd_total_oleo_reator);
    printf("\n");

    if(qtd_total_oleo_reator >= 1.25 && qtd_total_etoh_reator >= 2.50 && qtd_total_naoh_reator >= 1.25)
    {

        ativa_reator = 1;
        printf("\n\nREATOR ATIVADO");
        qtd_total_oleo_reator = qtd_total_oleo_reator - 1.25;
        qtd_total_etoh_reator = qtd_total_etoh_reator - 2.50;
        qtd_total_naoh_reator = qtd_total_naoh_reator - 1.25;
        qtd_mistura = 5;

        std::thread TQ_DEC(decantador,qtd_mistura);
        TQ_DEC.join();

    }
    else
    {
        std::thread TQ_DEC2(decantador,0);
        TQ_DEC2.join();

    }

}

void tanque_naoh_etoh() //Gabriel
{

    printf("\n\nTANQUE NAOH/ETOH:");

    printf("\nQUANTIDADE TOTAL DE ETANOL: %.3fL", qtd_etoh);
    printf("\nQUANTIDADE TOTAL DE HIDROXIDO DE SODIO: %.3fL", qtd_naoh);
    qtd_naoh = qtd_naoh + 0.25;
    qtd_etoh = qtd_etoh + 0.125;

    std::thread TQ_REATOR(reator, 0.0, 0.25, 0.125);
    TQ_REATOR.join();

}

void tanque_oleo(float qtd_oleo) //Lucas
{
    printf("\n\nTANQUE DE OLEO:");

    if(tempo_oleo == 5 )
    {
        float qtd_total_oleo = 0;
        printf("\nRecebendo %.3fL de oleo...", qtd_oleo);
        qtd_total_oleo = qtd_total_oleo + qtd_oleo;
        tempo_oleo = 1;

        if(qtd_total_oleo >= 1.25)
        {

            qtd_total_oleo = qtd_total_oleo - 1.25;
            printf("\nEnviando 1.250L de oleo para o reator. ");
            printf("\nQuantidade de oleo restante: %.3fL. ", qtd_total_oleo);

            std::thread TQ_REATOR2(reator, 1.25, 0.0, 0.0);
            TQ_REATOR2.join();
        }
        printf("\n\n");
    }
    else
    {
        printf("\n Tanque de oleo: ainda nao abastecido.");
        tempo_oleo++;
    }


}

int main(int argc, char** argv) //Gabriel
{
    using namespace std;
    int tempo = clock();

    while(1)
    {
        int j;
        srand(time(NULL));
        j=rand()%10;
        qtd_oleo =(float)j/10+1;

        thread TQ_OLEO(tanque_oleo, qtd_oleo);
        TQ_OLEO.join();

        thread TQ_ETANOL_NAOH(tanque_naoh_etoh);
        TQ_ETANOL_NAOH.join();

        Sleep(10000);
    }

    return 0;
}