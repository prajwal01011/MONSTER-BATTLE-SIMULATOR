#include <iostream>
#include<string.h>
#include<chrono>
#include<thread>
using namespace std;
//utilities
#ifdef _win32
    #include <Windows.h>
#endif

void sleepMs(int ms){
    this_thread::sleep_for(chrono::milliseconds(ms));
}
class Monster{
    private:
    string type;
    string name;
    int hp;
    int maxHP;
    int attackDamage;
    string icon;

    public:
    Monster(
        string type,
        string name,
        int hp,
        int attackDamage,
        string icon
    )
    :type(type)
    ,name(name)
    ,hp(hp)
    ,maxHP(hp)
    ,attackDamage(attackDamage)
    ,icon(icon)
    {}

    int getHP(){
        return hp;
    }

    string getIcon(){
        return icon;
    }

    string getName(){
        return name;
    }

    void setMonsterName(string MonsterName){
        name = MonsterName;
    }
    bool isAlive(){
        return (hp>0);
    }
    void displayStatus()
    {
        cout<<name<<"|"<<icon<<"\n";
        cout<<"HP:"<<hp<<"/"<<maxHP<<"\n";

    }
    void attack(Monster& target){
        cout<<name<<" attacks! with power "<<attackDamage<<"\n";
        target.takeDamage(attackDamage);
    }

    void takeDamage(int damage){
        hp=hp - damage;
        if(hp<0){
            hp=0;
        }
    }
};


Monster createYourMonster(int SelectedMonster){

    switch(SelectedMonster)
    {
        case 1:
        return Monster("Dragon", "",120, 12, "🐲");
        
        case 2:
            return Monster("wolf", "", 90, 16, "🐺");

        case 3:
            return Monster("Slime", "",150, 30, "🪩");

        case 4:
            return Monster("Bear", "",  180, 7, "🐻‍❄️");

        default:
            return Monster("","",0,0,"");
    }

}


//welcome screen
void showWelcomeScreen(){
    cout<<" ███╗   ███╗ ██████╗ ███╗   ██╗███████╗████████╗███████╗██████╗ \n";
    cout<<" ████╗ ████║██╔═══██╗████╗  ██║██╔════╝╚══██╔══╝██╔════╝██╔══██╗\n";
    cout<<" ██╔████╔██║██║   ██║██╔██╗ ██║███████╗   ██║   █████╗  ██████╔╝\n";
    cout<<" ██║╚██╔╝██║██║   ██║██║╚██╗██║╚════██║   ██║   ██╔══╝  ██╔══██╗\n";
    cout<<" ██║ ╚═╝ ██║╚██████╔╝██║ ╚████║███████║   ██║   ███████╗██║  ██║\n";
    cout<<" ╚═╝     ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝   ╚═╝   ╚══════╝╚═╝  ╚═╝\n";
    cout<<"\n";
    cout<<"                 B A T T L E   S I M U L A T O R \n";
    cout<<"\n";    
    cout<<"                      Select Your Moster:\n";
    cout<<"                      1.Dragon (HP 120 ATK 12)\n";
    cout<<"                      2.WOlf   (HP 90 ATK 16)\n";
    cout<<"                      3.Slime  (HP 150 ATK 30)\n";
    cout<<"                      4.Bear  (HP 180 ATK 7)\n";
}


void clearScreen(){

    #ifdef _win32
    system("cls");
    #else
    system("clear");
    #endif
}

void drawWalking(int page, string monsterType){
    clearScreen();
    cout<<"================================\n";
    cout<<"============EXPLORING===========\n";
    cout<<"================================\n\n";
    //draw/put trees
    for(int i=0;i<60;i++){

        if((i+page) %15 == 0){
            cout<<"🌴";
        }
        else{
        cout<<" ";
        }
    }
    cout<<"\n";
    //draw ground
    for(int i=0;i<60;i++){
        cout<<"-";
    }
    cout<<"\n";

    //draw monster
    for(int i=0;i<20;i++){
        cout<<" ";


    }
cout<<monsterType<<"\n\n";
cout<<"walking...\n";


}

void drawBattle(Monster& playerMonster, Monster& enemyMONster){

    clearScreen();
    cout<<"----------------------"<<"\n";
    cout<<"-------Battle---------"<<"\n";
    cout<<"----------------------"<<"\n";

    playerMonster.displayStatus();
    cout<<"                        vs\n\n";
    enemyMONster.displayStatus();
}

void monsterBattle(Monster& playerMonster, Monster& enemyMonster){

    while(playerMonster.isAlive() && enemyMonster.isAlive())
    {
        drawBattle(playerMonster,enemyMonster);
        playerMonster.attack(enemyMonster);
        sleepMs(1500);

        drawBattle(playerMonster,enemyMonster);
        if(enemyMonster.getHP()>0)
        {
        enemyMonster.attack(playerMonster);
        sleepMs(1500);
        }
        
    }



}

void startAdventure(Monster& playerMonster)
    {
       clearScreen();
        cout<<"Adventure has started!\n";
        
        int totalPages = 100;

        for(int pages=0;pages<totalPages;pages++){
            drawWalking(pages, playerMonster.getIcon());

            if((pages!=0)&&(pages%20==0)){
                clearScreen();
                cout<<"Enemy Monster Encountered!\n";

                sleepMs(1000);//1 second wait

                Monster enemyMonster("Goblin", "Goblin Minion",60, 1, "👺");
                monsterBattle(playerMonster,enemyMonster);
            }
            if(!playerMonster.isAlive())
            {
                break;
            }

            //the lower value the faster animation
            sleepMs(120);
        }
        if(playerMonster.isAlive())
        {
            cout<<"\n";
            cout<<"A powerful aura can be felt...\n";
            Monster enemyBoss("Boss","Goblin Boss",100,50, "⚔️🧌⚔️");
            sleepMs(2000);

            monsterBattle(playerMonster,enemyBoss);

            if(playerMonster.isAlive()){
                clearScreen();
                cout<<"Level cleared!\n";

            }
            else{
                cout<<"\n";
                cout<< playerMonster.getName()<<" Fainted...\n";
            }
        }
        else{
            clearScreen();
            cout<<"\n";
            cout<<playerMonster.getName()<<" Fainted..\n";
        }
      

}


int main(){

    #ifdef _win32
        SetConsoleOutputCP(CP_UTF8);
    #endif

    showWelcomeScreen();


    int SelectedMonster;
    string MonsterName;

    cin >> SelectedMonster;
    Monster playerMonster = createYourMonster(SelectedMonster);
    if( playerMonster.getHP()== 0){
        cout<<"You died cause you were too dumb";
        return 0;
    }



    cout<<"Enter Your Monster's Name:";
    cin>>MonsterName;

    playerMonster.setMonsterName(MonsterName);

    startAdventure(playerMonster);
    
    return 0;
}