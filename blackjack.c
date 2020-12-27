/*
---------------------------------------------------------------
Ôïýöáò Êùíóôáíôßíïò
ÁÅÌ: 2416
---------------------------------------------------------------
ÁÑÉÓÔÏÔÅËÅÉÏ ÐÁÍÅÐÉÓÔÇÌÉÏ ÈÅÓÓÁËÏÍÉÊÇÓ
ÔÌÇÌÁ ÐËÇÑÏÖÏÑÉÊÇÓ
ÂÁÓÉÊÅÓ ÁÑ×ÅÓ ÐÑÏÃÑÁÌÌÁÔÉÓÌÏÕ
1o ÅÎÁÌÇÍÏ
PROJECT 2013-14
$$$$$$--BLACKJACK--$$$$$$
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <windows.h>

void refresh_deck(int in_deck[10],int *number_of_avail_cards);
int pick_card(int c_deck[10],int pl,int *numofcards);
void print_card(int card);
int dealer_gameplay(int dg_dealer,int dg_dl_pts ,int dg_pl_pts,int *dg_pot,int dg_plr_bet,int *dg_pl_budget, char gamemode,int op_player);

//#####-GLOBAL VARIABLES-#####
int num_of_players, pc_player,pc_last_round;
//############################
int main()
{

    /*-----------------------------------------------------------
                     ÐÁÑÏÕÓÉÁÓÇ ÔÏÕ ÐÁÉ×ÍÉÄÉÏÕ
    ------------------------------------------------------------*/
    printf("----------------------------------------\nARISTOTLE UNIVERSITY OF THESSALONIKI\nToufas Konstantinos\nAEM:2416\n1st semester project 2013-2014\nProgramming in C\n----------------------------------------");
    printf("\n\t###############################\n\t#  $_$_$_$_BLACKJACK_$_$_$_$  #\n\t###############################\n\n");

    //------------------------------------------------------------
     srand(time(NULL));
    char *players_names[11],temp_name[30];
    int i,*players_budget,starting_bet,starting_budget;

    //ÅéóáãùãÞ ôïõ áñéèìïý ôùí ðáéêôþí

    printf("Insert the number of human players <MAX 10>: ");
    do
    {
    scanf("%d",&num_of_players);
    if(num_of_players>10) printf("\nMAX number of human players is 10! Insert a valid number: ");
    if(num_of_players<1) printf("\nAt least one human player must play in the game! Insert a valid number: ");
    }while(num_of_players>10 || num_of_players<1);

    //Ï õðïëïãéóôÞò ðñïóôßèåôáé áõôüìáôá óáí ðáß÷ôçò óôçí ôåëåõôáßá èÝóç ìåôÜ áðü üëïõò ôïõò õðüëïéðïõò ðáß÷ôåò
    pc_player = num_of_players;
    num_of_players++;

    printf("\n########-PLAYERS INFO-########\n\n");

    //ÅéóáãùãÞ ôùí ïíïìÜôùí ôùí ðáéêôþí

    for(i=0;i<num_of_players-1;i++)
    {
       printf("Insert the name of player %d: ",i+1);
       fflush(stdin);
       gets(temp_name);
       players_names[i] = (char *) malloc(strlen(temp_name)+1*sizeof(char)); //CHECK??
       strcpy(players_names[i],temp_name);
    }
    //Ðñïóôßèåôáé ôï üíïìá ôïõ õðïëïãéóôÞ
    players_names[num_of_players-1]=(char *)malloc(10*sizeof(char));
    strcpy(players_names[num_of_players-1],"PC_Player");

    //ÅéóáãùãÞ ôïõ áñ÷éêïý ðïóïý ìå ôï ïðïßï èá îåêéíÞóïõí ïé ðáß÷ôåò
    printf("\nInsert the starting budget <MIN=100>: ");
    do
    {
    scanf("%d",&starting_budget);
    if(starting_budget<=0) printf("\nPlease insert a valid number: ");
    }while(starting_budget<100);
    //Áñ÷éêïðïßóçóç ôïõ ëïãáñéáóìïý êÜèå ðáß÷ôç ìå ôï ðïóü ðïõ äüèçêå
    players_budget = (int *) calloc(num_of_players,sizeof(int));
    for(i=0;i<num_of_players;i++)
        players_budget[i]=starting_budget;

    printf("\n-------------PLAYER INFORMATION AND GAME OPTIONS SET HAS BEEN COMPLETED------------\n");
    Sleep(1000);
    //ÏËÏÊËÇÑÙÈÇÊÅ Ç ÅÉÓÏÄÏÓ ÔÙÍ ÓÔÏÉ×ÅÉÙÍ ÔÙÍ ÐÁÉÊÔÙÍ
  pc_last_round=starting_budget;

    /*
    Ç ôñÜðïõëá áðïôåëåßôáé áðï ôá öýëëá 7,8,9,10,J,Q,K,A
    êáé éó÷ýåé 7=7(points),8=8,9=9,10=10,J=2,Q=3,K=4,A=11
    êáé Ý÷ïõìå óõíïëï 32 öýëëá (8 öýëëá X 4 ÷ñùìáôá). Ïé äÝéêôåò óôïí ðßíáêá ðñïêýðôïõí ùò åîÞò: deck[CARD-2].
    ð.÷. deck[0]=deck[J-2]=deck[2-2]
    deck[0]=2=J,deck[1]=3=Q,deck[2]=4=K,deck[5]=7,deck[6]=8,deck[7]=9,deck[8]=10,deck[9]=11=A
    Ïé deck[3] êáé deck[4] äåí ÷ñçóéìïðïéýíôáé...
    */

    int deck[10],card,dealer_start_points=0;

    int *players_points;
    players_points = (int *) calloc(num_of_players,sizeof(int));

        //H cards_left ÷ñçóéìïðïéåßôáé ãéá íá äåß÷íåé ðüóá öýëëá ìÝíïõí óôçí ôñÜðïõëá êáé Üñá íá îÝñïõìå Üìá ÷ñåéÜæåôáé íá áíáíåùèåß ç ôñÜðïõëá ìáò ãéá íá ðáßîïõí êáé ïé õðüëïéðïé ðáß÷ôåò
        int cards_left;


//Áñ÷éêïðïßçóç ôçò ôñÜðïõëáò
            refresh_deck(deck,&cards_left);

    //ÅÄÙ ÅÉÍÁÉ ÔÏ ÓÇÌÅÉÏ ÐÏÕ ÐÑÅÐÅÉ ÍÁ ÅÐÉËÅÃÅÉ ÔÕ×ÁÉÁ Ï ÐÁÉ×ÔÇÓ ÐÏÕ ÈÁ ÎÅÊÉÍÇÓÅÉ ÙÓ ÌÁÍÁ
    int s_dealer;
    Sleep(1000);
    s_dealer = (rand() % num_of_players);

    //--------------ÎÅÊÉÍÁÅÉ ÔÏ ÐÁÉ×ÍÉÄÉ-----------------------


    int rounds,sets=0;

    int start_pot;
     int pot;
     int available_players=num_of_players; // Ï áñéèìüò ôùí ðáéêôþí ðïõ ðáñáìÝíïõí óôï ðáé÷íßäé (Áñ÷éêÜ åßíáé üëïé)
//------------------ÎÅÊÉÍÁÅÉ ÔÏ ÓÅÔ-----------------------------
do
{
    sets++;
    rounds=0;
    system("cls");
   printf("\t---------------SET %d----------------",sets);
     printf("\n\nPlayer %s  is the dealer",players_names[s_dealer]);
    //Åêêßíçóç ôïõ óåô ìå ôï áñ÷éêü ðïíôÜñéóìá ôïõ dealer
    printf("\n\nDealer (%s) enter the starting bet <MAX=%d>: ",players_names[s_dealer],players_budget[s_dealer]);
    if (s_dealer == pc_player)
    {
        /*
        Áí ï dealer åßíáé ï pc_player, ôï áñ÷éêü ðïíôÜñéóìá åßíáé ôï 15% ôïõ ëïãáñéáóìïý ôïõ (áí ôá ëåöôÜ ðïõ Ý÷åé äéáèÝóéìá
        åßíáé ðåñéóóüôåñá áðü ôï 50% ôïõ áñ÷éêïý budget ôïõ, áí åßíáé ëéãüôåñá ôï 10%, êáé áí åßíáé ðåñéóóüôåñá áðü ôï áñ÷éêü budget ôïõ ôüôå ôï 20%
        */
        if(players_budget[s_dealer]>starting_budget)
            pot=(int)(0.2*players_budget[s_dealer]);
        else if(players_budget[s_dealer]>starting_budget/2)
            pot=(int)(0.15*players_budget[s_dealer])+1;
        else
            pot=(int)(0.1*players_budget[s_dealer]);
    }

    else
    {

        scanf("%d",&pot);
        while(pot<=0 && pot>starting_budget)
        {
            printf("\nPlease enter a valid bet 0<bet<=%d: ",starting_budget);
            scanf("%d",starting_bet);
        }
    }
    players_budget[s_dealer]-=pot;
    printf("\nDealer (%s) bet %d in the pot\nPot = %d",players_names[s_dealer],pot,pot);
    Sleep(1500);
    start_pot = pot;

int play_final_round=1; //Ç ìåôáâëçôÞ áõôÞ åßíáé ÷ñçóéìïðïéåßôáé ùò flag ãéá ôç óõíÝ÷åéá ôïõ óåô. Áí åßíáé 1 óçìáßíåé üôé ôï óåô óõíå÷ßæåé êáíïíéêÜ ÷ùñßò íá âñéóêüìáóôå óôïí
                        //ôåëåõôáßï ãýñï (áõôïí ðïõ ðáßæåôáé áí ç êÜâá (õðåñ)ôñéðëáóéáóôåß áðü ôçí áñ÷éêÞ). Áí åßíáé 2 óçìáßíåé üôé ðáßæåôáé ï ôåëåõôáßïò ãýñïò. Áí åßíáé 0 óôáìáôÜåé ôï óåô.

//ÎÅÊÉÍÁÅÉ ÅÍÁ ÓÅÔ ÌÅ ÌÁÍÁ ÔÏÍ ÐÁÉÊÔÇ s_dealer
while(play_final_round && pot>0)
{

    rounds++;
    Sleep(1500);
system("cls");
    printf("\t---------------SET %d----------------",sets);
printf("\n\n\t---------------ROUND %d--------------\n\n",rounds);
printf("DEALER: %s",players_names[s_dealer]);
printf("\nPOT=%d",pot);


      //Áíáíåþíïíôáéôá öýëëá óôçí ôñÜðïõëá ãéá íá îåêéíÞóåé ç ãýñá
    refresh_deck(deck,&cards_left);
       //Ç ÐÑÙÔÇ ÌÏÉÑÁÓÉÁ ÔÙÍ ÊËÅÉÓÔÙÍ ÖÕËËÙÍ
    for(i=0;i<num_of_players;i++)
        players_points[i] = 0; //Óå êÜèå ãýñï ïé ðüíôïé ôùí ðáé÷ôþí ìçäåíßæïíôáé
    printf("\nClosed cards are dealed...");
    for(i=0;i<num_of_players;i++)
     {
         //ÌïéñÜæïõìå ìüíï óôïõò ðáß÷ôåò ðïõ óõíå÷ßæïõí óôï ðáé÷íßäé, êáé ÷ùñßò ôïí dealer, ãéáôß èá ðÜñåé ðéï êÜôù
         if(players_budget[i]>0 && i!=s_dealer)
         {
        card=pick_card(deck,i,&cards_left);
        players_points[i] += card+2; //ÂÜæïõìå card+2 ãéáôß ç ðñáãìáôéêÞ áîßá ôçò êÜñôáò åßíáé ï äåßêôçò ôïõ deck (äçëáäÞ ôï card) + 2
         }
     }



    //ÎÅÊÉÍÁÅÉ ÌÉÁ ÃÕÑÁ ÌÅ ÏËÏÕÓ ÔÏÕÓ ÐÁÉÊÔÅÓ ÐÏÕ ÓÕÍÅ×ÉÆÏÕÍ
    int plr,plr_bet;
    for(plr=0;plr<num_of_players && pot>0;plr++) //ÐñÝðåé ç êÜâá íá åßíáé ìåãáëýôåñç ôïõ 0 ãéá íá ìðïñåß íá óõíå÷éóôåß ôï ðáé÷íßäé êáé ìå ôïõò Üëëïõò ðáß÷ôåò
    {
        if(players_budget[plr]>0 && plr !=s_dealer) //Ç ãýñá ìðïñåß íá ðáé÷ôåß ìüíï áí ï ðáß÷ôçò Ý÷åé ëåöôÜ ãéá íá ðïíôÜñåé, êáé ï ðáß÷ôçò ðïõ ðáßæåé óáí dealer êÜíåé äéêü ôïõ ðáé÷íßäé
        {
        //ÐïíôÜñéóìá ðáß÷ôç
            if(plr!=pc_player)
            {
        printf("\n\n$$$--!PLAYER %s'S TURN!--$$$\n\nMoney left in budget: %d\n",players_names[plr],players_budget[plr]);
         printf("\nPlayer %s your closed card is ",players_names[plr]);
        print_card(players_points[plr]);
        printf("\nHow much money would you like to bet?<MAX BET=%d>: ",pot);
        scanf("%d",&plr_bet);
        //ÅËÅÃ×ÏÉ ÐÏÍÔÁÑÉÓÌÁÔÏÓ:
        if(plr_bet==0)
        {
            printf("\nOk you don't want to play in this round!\nMove on to the next player!\n");
            continue;
        }
        while(plr_bet>pot || players_budget[plr]<plr_bet)
        {
            if(players_budget[plr]<plr_bet) //Áí ôï ðïóü ðïõ èÝëåé íá ðïíôÜñåé ï ðáßêôçò äåí åßíáé äéáèÝóéìï óôïí ëïãáñéáóìï ôïõ
                printf("\nYou don't have enough money in your budget");
            else //Ç áí èÝëåé íá ðïíôÜñåé ðéï ðïëëÜ ëåöôÜ áðü áõôá ðïõ ðüíôáñå ï dealer
                printf("\nYour bet must not be greater than MAX BET");
            printf("\nPlease insert the amount of money you would like to bet correctly");
            fflush(stdin);
            scanf("%d",&plr_bet);
        }

            }
            else //ÐÏÍÔÁÑÉÓÌÁ ÔÏÕ PC_PLAYER
            /*
            Ôï ðïíôÜñéóìá ôïõ pc_player êáôá ôç äéÜñêåéá ôùí ãýñùí Ý÷åé ðÜíù êÜôù ôçí ßäéá ëïãéêÞ ìå ôï áñ÷éêü ðïíôÜñéóìá (óýãêñéóç ôïõ äéáèÝóéìïõ ðïóïý ðïõ ôïõ Ý÷åé ìåßíåé ìå ôï áñ÷éêü)
            êáé ðñïóáõîÜíåôáé áíÜëïãá ìå ôá êÝñäç ðïõ Ý÷åé óå êÜèå ãýñï, êáé ôïí áñéèìü ôùí ðáéêôþí ðïõ áðï÷ùñïýí(áõîÜíïíôáò 2% ôï óôïß÷çìá ãéá êÜèå ðáßêôç ðïõ Ý÷åé öýãåé), îåêéíþíôáò áðü ôï 15% ôïõ áñ÷éêïý ðïóïý!
            */
            {

                int mdif,pldif,k; //H ÷ñçìáôéêÞ äéáöïñÜ óôïí ëïãáñéáóìü ôïõ pc_player ìåôáîõ ôïõ ðñïçãïýìåíïõ êáé áõôïý ôïõ ãýñïõ (ÓÔÏÍ ÐÑÙÔÏ ÃÕÑÏ ÅÉÍÁÉ 0)
                k=0;
                do
                {
                    if(players_budget[plr]>starting_budget) //Áí ðçãáßíåé êáëÜ èá óôïé÷çìáôßæåé ìå âÜóç ôï pot, áëëéþò ìå âÜóç ôïí ëïãáñéáóìü ôïõ
                        plr_bet=(int)(0.2*pot); //Áñ÷ßæåé ìå 20% ôïõ Pot
                    else if(players_budget[plr]>starting_budget/2)
                    {
                        if (players_budget[plr]>pot)
                            plr_bet=(int)(0.1*pot); //Áñ÷ßæåé ìå 10% ôïõ Pot
                        else
                            plr_bet=(int)(0.1*players_budget[plr]); //Áñ÷ßæåé ìå 10% ôïõ ëïãáñéáóìïý
                    }
                    else
                        plr_bet=(int)(0.05*players_budget[plr]); //Áñ÷ßæåé ìå 5% ôïõ Pot

                mdif=pc_last_round-players_budget[plr];
                if(mdif>0) //Áí mdif>ï óçìáßíåé üôé óôïí ðñïçãïýìåíï ãýñï ï ðáßêôçò åß÷å êÝñäïò, ôï 50% ôïõ ïðïßïõ èá ðñïóôåèåß óôï óôïß÷çìá
                    plr_bet+=(int)(0.5*mdif);
                else //Áëëéþò èá áöáéñåèåß
                    plr_bet-=(int)(0.5*mdif);
               pldif=num_of_players-available_players;
               plr_bet= (int)(plr_bet*(1+0.02*pldif));
               //Óå ðåñßðôùóç ðïõ ðñïêýøåé êÜðïéï èÝìá ìå ôï ðïíôÜñéóìá êáé ÷ñåéáóôåß íá ìåéùèåß, èá ìåéþíåôáé êáôá 10% êÜèå öïñÜ ìÝ÷ñé íá ìðåé óôá åðéèõìçôÜ üñéá
               plr_bet -= (int)(k*0.1*plr_bet);
               k++;
                }while(plr_bet>pot || plr_bet>players_budget[plr]);
            }
            printf("\n\nPlayer %s bet %d",players_names[plr],plr_bet);
        //Ïëïêëçñþèçêå ôï ðïíôÜñéóìá ôïõ ðáß÷ôç êáé ôï ðïóü âñßóêåôáé óôç ìåôáâëçôÞ plr_bet

        //-------PLAYER'S GAME-------
        char pl_cont;
        int *player_round_cards,prc_counter=1;
        player_round_cards = (int *) calloc(32,sizeof(int)); //Ðéíáêáò ðïõ ÷ñçóéìïðïéåßôå ãéá íá áðïèçêÝõåé ôéò êÜñôåò ðïõ ôñáâÜåé ï ðáß÷ôçò êáôá ôç äéÜñêåéá ôïõ ãýñïõ
        player_round_cards[0]=players_points[plr]-2; //Óôçí èÝóç 0 ìðáßíåé ôï êëåéóôü öýëëï ðïõ ðÞñå ï ðáß÷ôçò óôçí ðñþôç ìïéñáóéÜ
        printf("\n\nCARDS:\n");
        print_card(player_round_cards[0]+2);
        printf("\tTotal points: %d\n",players_points[plr]);
        printf("\nDo you want to pick another card?[Y/N]: ");
        if(plr!=pc_player) //ÐÁÉÆÅÉ HUMAN PLAYER
        {
        //ÐñÝðåé íá ãßíåé åñþôçóç

            do
            {
                fflush(stdin);
                scanf("%c",&pl_cont);
                if(pl_cont!='y' && pl_cont!='Y' && pl_cont!='n' && pl_cont!='N') printf("\nPlease enter 'Y' or 'N':");
            }
            while(pl_cont!='y' && pl_cont!='Y' && pl_cont!='n' && pl_cont!='N');
        }
        else //O pc_player ðáíôá ôñáâÜåé äåõôåñç êÜñôá êáèþò äåí õðÜñ÷åé ðåñßðôùóç íá êáåé óôçí äåõôåñç
        {
            printf("\nYes, deal me!");
            pl_cont='y';
        }

        while(pl_cont=='Y' || pl_cont=='y') //¼óï ï ðáß÷ôçò óõíå÷ßæåé íá ðáßæåé...
        {
            //Ï ðáßêôçò äéÜëåîå íá ôñáâÞîåé êÜñôá
            int r_card;
            r_card=pick_card(deck,plr,&cards_left);
            prc_counter++; //Counter ðïõ äåß÷íåé ðüóåò êÜñôåò Ý÷åé ôñáâÞîåé óôïí ãýñï áõôü ï ðáßêôçò
            player_round_cards[prc_counter-1]=r_card; //Áðïèçêåýåôáé ç êÜñôá ðïõ ìüëéò ôñÜâçîå ï ðáß÷ôçò
            printf("\nYou picked: ");
            print_card(r_card+2);

            //ÅÉÄÉÊÇ ÐÅÑÉÐÔÙÓÇ ÐÏÕ ÔÁ ÄÕÏ ÐÑÙÔÁ ÖÕËËÁ ÅÉÍÁÉ ÁÓÓÏÉ
            if((player_round_cards[0]+2)==11 && (player_round_cards[1]+2)==11)
                players_points[plr]=21;
            else
                players_points[plr]+=r_card+2; //Ðñïóôßèåíôáé ïé ðüíôïé óôïõò óõíïëéêïýò ôïõ ðáß÷ôç

            printf("\nCARDS\n");
            for(i=0;i<prc_counter;i++) //ÎáíáðáñïõóéÜæïíôáé óôïí ðáß÷ôç ôá äåäïìÝíá ìåôÜ êáé ôï ôåëåõôáßï ôñÜâçãìá
                print_card(player_round_cards[i]+2);
            printf("\tTotal points: %d",players_points[plr]);

            //4 ÐÅÑÉÐÔÙÓÅÉÓ ÐÁÉ×ÍÉÄÉÏÕ

            if(players_points[plr]==21) //1ïí) Ïé ðüíôïé ôïõ ðáß÷ôç åßíáé 21 Üñá êåñäßæåé áõôüìáôá ôïí ãýñï
            {
                if(plr==pc_player) pc_last_round=players_budget[plr];
                players_budget[plr]+=plr_bet;
                pot -= plr_bet;
                printf("\nYOU HAVE 21 POINTS!! YOU WIN THE ROUND!!");
                pl_cont='s';
            }
            else if(players_points[plr]>21) //Ï ðáß÷ôçò îåðÝñáóå ôïõò 21 ðüíôïõò Üñá ÷Üíåé áõôüìáôá ôïí ãýñï
            {
               if(plr==pc_player) pc_last_round=players_budget[plr];
                players_budget[plr]-=plr_bet;
                pot += plr_bet;
                printf("\nYOU EXCEEDED 21 POINTS... YOU LOSE THE ROUND");
                pl_cont='s';
            }
            else
                if(prc_counter==5)//Ï ðáß÷ôçò ôñÜâçîå ðÝíôå öýëëá êáé äåí ìðïñåß íá ôñáâÞîåé Üëëï
                {
                    printf("\nYOU HAVE PICKED MAX 5 CARDS");
                    pl_cont='m';
                }
                else
                {
                    printf("\nDo you want to pick another card?[Y/N]: ");//Ï ðáß÷ôçò óõíå÷ßæåé íá ôñáâÜåé
                    if(plr!=pc_player)
                    {

                    do
                    {
                    fflush(stdin);
                    scanf("%c",&pl_cont);
                    if(pl_cont!='y' && pl_cont!='Y' && pl_cont!='n' && pl_cont!='N') printf("\nPlease enter 'Y' or 'N': ");
                    }while(pl_cont!='y' && pl_cont!='Y' && pl_cont!='n' && pl_cont!='N');

                    }
                    else
                    {

                        //Áí ïé ðüíôïé ôïõ pc_player åßíáé <17 ç áí åßíáé ðåñéóóüôåñïé êáé ç ðéèáíüôçôá óõíå÷ßæåé íá ôñáâÞîåé ÷ñÞóéìï öýëëï åßíáé ìåãáëýôåñç
                        //áðü 80% ôüôå óõíå÷ßæåé íá ôñáâÜåé
                        if(players_points[plr]<17)
                        {
                            printf("\nYes, deal me!");
                            Sleep(2000);
                            pl_cont='y';
                        }
                        else
                        {
                            int dif,q,prob,c_sum=0;
                            dif=21-players_points[plr]; //Ìå÷ñé ôé öýëëï ÷ñåéÜæåôáé ãéá 21
                            for(q=0;q<10;q++)
                                if((q+2)<=dif) c_sum += deck[q];
                            prob=(c_sum / cards_left)*100;
                            if(prob>=80) //Áí ç ðéèáíüôçôá íá ôñáâÞîåé êáëü öýëëï åßíáé >=80%
                            {
                            printf("\nYeah i'll take the risk! Deal me!");
                            Sleep(2000);
                            pl_cont='y';
                            }
                            else //Áëëéþò óôáìáôÜåé
                            {
                            printf("\nNo, I'm ok!");
                            Sleep(2000);
                            pl_cont='n';

                            }
                        }//teleiwnei
                    }
                    if(pl_cont=='n' || pl_cont=='N') printf("\nPlayer %s decided to stop",players_names[plr]);
                }

        }

        free(player_round_cards); //Ï ÷þñïò ðïõ áðïèçêåõüôáí ïé êÜñôåò ôïõ ðáß÷ôç äåí ÷ñåéÜæåôáé Üëëï êáé áðïäåóìåýåôáé

        //-------------ÔÅËÅÉÙÓÅ ÔÏ ÐÁÉ×ÍÉÄÉ ÔÏÕ ÐÁÉ×ÔÇ... ÁÑ×ÉÆÅÉ ÔÏ ÐÁÉ×ÍÉÄÉ ÔÏÕ DEALER--------------------------------------

if(pl_cont =='N' || pl_cont =='n' || pl_cont=='m') //Áí ï ðáß÷ôçò ôñÜâçîå 5 öýëëá Þ óôáìÜôçóå íá ôñáâÜåé ðñÝðåé íá ðÜéîåé ï dealer
  {
      printf("\n\n!DEALER'S (%s) TURN!",players_names[s_dealer]);


            int *dealer_round_cards,dr_card,drc_counter=1,pts_limit=17;
            char dl_play = 1;
            //Ìçäåíßæïíôáé ïé ðüíôïé ôïõ dealer
      players_points[s_dealer]=0;
      //Ðáßñíåé êëåéóôü öýëëï
      dr_card = pick_card(deck,s_dealer,&cards_left);
      players_points[s_dealer]+=dr_card+2;
      printf("\nDealer's closed card is ");
      print_card(dr_card+2);

            dealer_round_cards = (int *) calloc(32,sizeof(int)); //Ðßíáêáò ãéá ôéò êÜñôåò ôïõ dealer
            dealer_round_cards[0]=players_points[s_dealer]-2; //Ç ðñþôç êÜñôá ôïõ dealer

if(pl_cont == 'm') //Ç ðåñßðôùóç ðïõ ï ðáß÷ôçò ôñÜâçîå 5 Üñá ï dealer ðñÝðåé íá ôñáâÜåé ìÝ÷ñé íá öôÜóåé 21 Þ íá êáåß
               {
               pts_limit = 21;
               printf("\n\nDealer %s, because player %s stopped after picking 5 cards, you have to pick cards until you get 21 points, or get burned!",players_names[s_dealer],players_names[plr]);
               }


            if(s_dealer==pc_player) //Ï dealer åßíáé ï PC_PLAYER ïðüôå ôï ðáé÷íßäé ôïõ ãßíåôáé áõôüìáôá
                    {
            while(dl_play) //¼óï ïé ðüíôïé ôïõ dealer åßíáé ìéêñüôåñïé áðü ôï üñéï
                {
                    printf("\nDealer will pick another card");
                    dr_card = pick_card(deck,s_dealer,&cards_left); //Ï dealer ôñáâÜåé êÜñôá
                    drc_counter++; //Ï áñéèìüò ôùí êáñôþí ðïõ Ý÷åé ôñáâÞîåé áõîÜíåôáé êáôá 1
                    dealer_round_cards[drc_counter-1]=dr_card; // ç êÜñôá ðïõ ôñÜâçîå áðüèçêåýåôáé óôïí ðßíáêá
                    //ÅÉÄÉÊÇ ÐÅÑÉÐÔÙÓÇ ÌÅ ÄÕÏ ÐÑÙÔÁ ÖÕËËÁ ÁÓÓÏÕÓ
                    if((dealer_round_cards[0]+2)==11 && (dealer_round_cards[1]+2)==11)
                        players_points[s_dealer]=21;
                    else
                        players_points[s_dealer]+=dr_card+2; //Ðñïóôßèåíôáé ïé ðüíôïé ôïõ dealer óôï óýíïëï
                    printf("\nDealer picked ");
                    print_card(dr_card+2);
                      printf("\n\nCARDS\n");
                        for(i=0;i<drc_counter;i++)
                            print_card(dealer_round_cards[i]+2);
                        printf("\tTotal points: %d\n",players_points[s_dealer]);

                    if(players_points[s_dealer] >= pts_limit) //ÓôáìáôÜåé ôï ðáé÷íßäé
                        dl_play=0;
                }


            //Ðáñïõóßáóç ôùí êáñôþí êáé ôùí ðüíôùí ôïõ dealer
                  dealer_gameplay(s_dealer,players_points[s_dealer],players_points[plr],&pot,plr_bet,&players_budget[plr],pl_cont,plr); //¼ôáí ï ðáß÷ôçò åßíáé ï PC_PLAYER ôüôå ç dealer_gameplay() åêôåëåßôáé ìüíï ìéá öïñÜ
                    }
             else //Ï dealer åßíáé HUMAN PLAYER
    {
        while(dealer_gameplay(s_dealer,players_points[s_dealer],players_points[plr],&pot,plr_bet,&players_budget[plr],pl_cont,plr)) //¼óï ï human dealer óõíå÷ßæåé íá ôñáâÜåé
        {
             dr_card = pick_card(deck,s_dealer,&cards_left); //Ï dealer ôñáâÜåé êÜñôá
             printf("\nDealer picked ");
             print_card(dr_card+2);
                    drc_counter++; //Ï áñéèìüò ôùí êáñôþí ðïõ Ý÷åé ôñáâÞîåé áõîÜíåôáé êáôá 1
                    dealer_round_cards[drc_counter-1]=dr_card; // ç êÜñôá ðïõ ôñÜâçîå áðüèçêåýåôáé óôïí ðßíáêá

                    //ÅÉÄÉÊÇ ÐÅÑÉÐÔÙÓÇ ÌÅ ÄÕÏ ÐÑÙÔÁ ÖÕËËÁ ÁÓÓÏÕÓ
                    if((dealer_round_cards[0]+2)==11 && (dealer_round_cards[1]+2)==11)
                        players_points[s_dealer]=21;
                    else
                        players_points[s_dealer]+=dr_card+2; //Ðñïóôßèåíôáé ïé ðüíôïé ôïõ dealer óôï óýíïëï

        //Ðáñïõóßáóç ôùí êáñôþí êáé ôùí ðüíôùí ôïõ dealer
            printf("\n\nCARDS\n");
            for(i=0;i<drc_counter;i++)
                  print_card(dealer_round_cards[i]+2);
            printf("\tTotal points: %d\n",players_points[s_dealer]);
        }

    }
            free(dealer_round_cards); //Áðïäåóìåýïõìå ôïí ÷þñï áðïèÞêåõóçò ôùí êáñôþí ôïõ dealer

  //---------------ÔÅËÅÉÙÍÅÉ ÔÏ ÐÁÉ×ÍÉÄÉ ÔÏÕ DEALER-------------------------------

  }
    //ÔÅËÏÓ ÃÕÑÏÕ! Áí ï ðáß÷ôçò Ý÷åé ÷Üóåé üëá ôá ëåöôÜ ôïõ âãáßíåé áð ôï ðáé÷íßäé
    if (players_budget[plr]==0)
    {
        printf("\nPlayer %s's budget = 0. Player exits from the game",players_names[plr]);
        available_players--;
    }
    //Eðßóçò êáé áí ï dealer Ý÷áóå üëá ôïõ ôá ëåöôÜ (äçëáäÞ åß÷å ôïðïèåôÞóåé üëï ôïõ ôï budget óáí áñ÷éêü ðïóü óôçí ìðÜíêá êáé áõôÞ ìçäåíßóôçêå) ðñÝðåé íá öýãåé
    if (players_budget[s_dealer]==0 && pot==0)
    {
        printf("\nPlayer %s's budget = 0. Player exits from the game",players_names[s_dealer]);
        available_players--;
    }
    Sleep(3000);
    }
    }
    /*
    Ôåëåßùóå Ýíáò ãýñïò ìå ôç ìÜíá íá Ý÷åé ðáßîåé ìå üëïõò ôïõò äéáèÝóéìïõò ðáß÷ôåò
    ÐñÝðåé íá ãßíåé Ýëåã÷ïò áí ç êÜâá åßíáé ôñéðëÜóéá áðü ôï start_pot þóôå íá ðáé÷ôåß ï ôåëéêüò ãýñïò
    */
    if (play_final_round == 2) //Ðïõ óçìáßíåé üôé óôçí ðñïçãïýìåíç ãýñá ç êÜâá åß÷å (õðåñ)ôñéðëáóéáóôåß óå ó÷Ýóç ìå ôï áñ÷éêü ðïóü ðïõ åß÷å ôïðïèåôÞóåé ç ìÜíá óôçí êÜâá Üñá ôï óåô ôåëåéþíåé åäþ
        {
        play_final_round=0; //Ôåëåéþíåé ôï óåô
        players_budget[s_dealer]+=pot; //Ôï ðïóü ðïõ ðåñéóóåøå óôçí êÜâá, ìåôÜ ôïí ôåëåõôáßï ãýñï ðñïóôßèåôáé óôïí ëïãáñéáóìü ôïõ dealer
        }
    if(pot>=3*start_pot && play_final_round!=0) //¸ëåã÷ïò ãéá ôåëéêü ãýñï
    {
        play_final_round = 2;
        printf("\n\nPot has been (over)tripled from the starting bet! FINAL ROUND!");
        Sleep(2000);
    }

    else if(pot==0)
        printf("\n\nPOT = 0. SET IS OVER");

Sleep(3000);
}
//----------ÔÅËÏÓ ÔÏÕ ÓÅÔ ÌÅ ÌÁÍÁ ÔÏÍ s_dealer--------------------------------
//ÐñÝðåé íá åðéëåãåß íÝïò s_dealer, ï ïðïßïò èá åßíáé ï "ðñïçãïýìåíïò êõêëéêÜ" ðáßêôçò áðï ôïí ôùñéíü, áöïý ðáßæïõìå ìå áíÜóôñïöç öïñÜ ôùí äåéêôþí ôïõ ñïëïãéïý
    s_dealer--;
    if(s_dealer == -1) s_dealer=(num_of_players-1); //Áí ï s_dealer Þôáí ï ðñþôïò ðáß÷ôçò ôüôå èá ðñÝðåé êõêëéêÜ íá åðéëåãÝé ï "ôåëåõôáßïò" ðáß÷ôçò
    //ÐñïóÝ÷ïõìå ðÜíôá ï ðáß÷ôçò íá Ý÷åé ëåöôÜ íá ðáßîåé!!
    while(players_budget[s_dealer]<=0)
    {
        s_dealer--;
        if(s_dealer == -1) s_dealer=(num_of_players-1);
    }
} while(available_players>1); //ÄçëáäÞ ôï ðáé÷íßäé óõíå÷ßæåôáé üóï õðÜñ÷ïõí ðåñéóóüôåñïé áðü Ýíáí ðáß÷ôåò ìå ëåöôÜ óôïí ëïãáñéáóìü ôïõò

//--------------------ÔÅËÅÉÙÓÅ ÔÏ ÐÁÉ×ÍÉÄÉ---------------------------------
//ÐñÝðåé íá âñïýìå ðïéïò êÝñäéóå, äçëáäÞ ðïéïò åßíáé ï ðáßêôçò ðïõ óõãêÝíôñùóå üëá ôá ëåöôÜ óôïí ëïãáñéáóìü ôïõ
int winner;
for(winner=0;winner<num_of_players;winner++)
    if(players_budget[winner]!=0)
    {
        printf("\n\nWE HAVE A WINNER!!!!!!!!!!CONGRATS PLAYER %s !!!!!!!!!!!",players_names[winner]);
        break;
    }

    printf("\n\nEND OF THE GAME\n");
    system("pause");
    return 0;
}


int pick_card(int c_deck[10],int pl, int *numofcards)
{
    int card;
    Sleep(1400); //Ç ÷ñçóéìüôçôá ôïõ Sleep åßíáé óôç rand()  ç ïðïßá ëüãù ôïõ ïôé åêôåëåßôáé óå äéÜóôçìá ìéêñüôåñï ôïõ åíüò äåõôåñïëÝðôïõ áðïäßäåé ôéò ßäéåò ôéìåò.
    card=(rand()+pl) % 10;

    if(*numofcards==0) //Áí ôï deck Üäåéáóå ôï áíáíåþíïõìå
        refresh_deck(c_deck,numofcards);

    while(c_deck[card]<1) //ÅëÝã÷ïõìå áí õðÜñ÷åé äéáèÝóéìï ôï öýëëï óôçí ôñÜðïõëá ìáò
        card=(rand()+pl) % 10;

        //Áí äåí õðÜñ÷åé äéáëÝãïõìå êÜðïéï Üëëï
    c_deck[card]--; //Êáé ôï áöáéñïýìå áðï ôá äéáèÝóéìá
    (*numofcards)--; //Ìåéþíïõìå êáé ôïí óõíïëéêü áñéèìü ôùí äéáèÝóéìùí öýëëùí
    return card;

}

void print_card(int card) //×ñçóéìïðïåßôáé ãéá ôçí åìöÜíéóç ôùí öýëëùí óôçí ïèüíç
{
    switch (card)
    {
    case 2:
        printf("J ");
        break;
    case 3:
        printf("Q ");
        break;
    case 4:
        printf("K ");
        break;
    case 11:
        printf("A ");
        break;
    default:
        printf("%d ",card);
    }
return;
}

void refresh_deck(int in_deck[10], int *number_of_avail_cards)
 /*
 Áíáíåþíåé ôçn ôñÜðïõëá óå ðåñßðôùóç ðïõ ôåëåéþóïõí ôá öýëëá
  */
{
    int i;
    for(i=0;i<10;i++)
        in_deck[i]=4;
    in_deck[3]=0; //Ôá deck[3],deck[4] äçëáäç ôï 5 êáé ôï 6 åßíáé öýëëá ðïõ äåí ÷ñçóéìïðïéïýíôáé. Ãé áõôü ëÝìå üôé ç ôñÜðïõëá ìáò
    in_deck[4]=0; //äåí ôá ðåñéÝ÷åé (ôá èÝôïõìå ßóá ìå ôï 0). Áõôï âïçèÜåé íá áðïöýãïõìå ðåñéôôïýò åëÝã÷ïõò
    *number_of_avail_cards=32;
return;
}

int dealer_gameplay(int dg_dealer,int dg_dl_pts ,int dg_pl_pts,int *dg_pot,int dg_plr_bet,int *dg_pl_budget, char gamemode,int op_player)
{
    char ans='p';
            if (dg_dl_pts==21)//Ï dealer Ý÷åé 21 ðüíôïõò êáé êåñäßæåé áõôüìáôá ôïí ãýñï
            {
                if(op_player==pc_player) pc_last_round=*dg_pl_budget;
                *dg_pot += dg_plr_bet;
                *dg_pl_budget -= dg_plr_bet;
                printf("\nDEALER HAS 21 POINTS! DEALER WINS THE ROUND");
            }

            else if(dg_dl_pts>21)//Ï dealer îåðÝñáóå ôïõò 21 ðüíôïõò êáé ÷Üíåé áõôüìáôá ôïí ãýñï
            {
                if(op_player==pc_player) pc_last_round=*dg_pl_budget;
               *dg_pot -= dg_plr_bet;
                *dg_pl_budget += dg_plr_bet;
                printf("\nDEALER HAS EXCEEDED 21 POINTS! PLAYER WINS THE ROUND");
            }
            else //ÐñÝðåé íá ãßíåé óýãêñéóç ôùí ðüíôùí ôïõ dealer êáé ôïõ ðáß÷ôç
            {
                if(dg_dealer != pc_player) //Áí ï dealer åßíáé human, ôüôå èá ðñÝðåé íá õðÜñ÷åé åñþôçóç ãéá ôï áí èÝëåé íá ôñáâÞîåé Üëëç êÜñôá
                    if (gamemode!='m')
                    {
                    printf("\nDealer would you like to pick another card?[Y/N]: ");
                    fflush(stdin);
                    do
                    scanf("%c",&ans);
                    while(ans!='y' && ans !='Y' && ans!='N' && ans!='n');
                    if(ans=='y' || ans=='Y')
                        return 1; //Áí èÝëåé, ç óõíÜñôçóç óôáìáôÜåé åäþ êáé ìå ôï 1 êáôáëáâáßíïõìå üôé ðñÝðåé íá ôñáâç÷ôåß êáé Üëëï öýëëï
                     }
                    else
                    {
                     return 1;

                    }        //Áí ï ðáßêôçò óôáìÜôçóå ìåôÜ áðü 5 öýëëá ÷ùñßò íá öôÜóåé 21, ôüôå ï dealer åßíáé õðï÷ñåùìåíïò íá ôñáâÜåé ìÝ÷ñé íá öôÜóåé 21 Þ íá êáåß. ÅðïìÝíùò äåí ÷ñåéÜæåôáé åñþôçóç
                               //ÁðëÜ ç óõíÜñôçóç åðéóôñÝöåé 1, äçëáäÞ óõíå÷ßæåé ôï ôñÜâçãìá

                //Áí äåí èÝëåé ãßíåôáé êáíïíéêÜ ç óýãêñéóç ôùí ðüíôùí ôïõ ìå ôïõò ðüíôïõò ôïõ ðáßêôç
                if(dg_dl_pts>=dg_pl_pts) //Dealer wins
                {
                    if(op_player==pc_player) pc_last_round=*dg_pl_budget;
                    *dg_pot += dg_plr_bet;
                    *dg_pl_budget -= dg_plr_bet;
                    printf("\nDealer decided to stop\n");
                    printf("\nDEALER's POINTS >= PLAYER's POINTS! DEALER WINS THE ROUND");
                }
                else //Player wins
                {
                   if(op_player==pc_player) pc_last_round=*dg_pl_budget;
                    *dg_pot -= dg_plr_bet;
                    *dg_pl_budget+= dg_plr_bet;
                    printf("\nDealer decided to stop\n");
                    printf("\nDEALER's POINTS < PLAYER's POINTS! PLAYER WINS THE ROUND");
                }
            }

    return 0;
}
