#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue) {
    // khai bao cac bien, xu li file
   int stmap=1, distmap, levelO, eventcode, count1, count2;
   int small=0,frog=0, nholevel, nhoHP,count_19=0,count_18=0;
   string mapcode,namefile,file_mush_ghost, file_merlin_pack, file_aclepius_pack;
   int *map = new int[10000]; // khoi tao con tro map
   read_file(file_input,mapcode,namefile,HP,level,remedy,maidenkiss,phoenixdown);
   xulyfile(mapcode,map,distmap);
   split_namefile(namefile,file_mush_ghost, file_merlin_pack, file_aclepius_pack);
   int MaxHP = HP;

    //xu li su kien
   do
    {   
       endgame(rescue,HP,stmap,distmap);
       int const_remedy=remedy;
       int eventcode = map[stmap-1];
       levelboss(levelO,stmap);
        stmap+=1;
        switch (eventcode)
        {
        case 0:
            rescue=1;
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            event1to5(HP, level, phoenixdown, rescue, eventcode, MaxHP, levelO, small,frog);
            break;
        case 6:
            if(small==0 && frog==0){
                nhoHP=HP;
                shaman(HP,level,remedy,eventcode,MaxHP,levelO,small,const_remedy);
                count1=0;
            }else;
            break;
        case 7:
            if(small==0 && frog==0){
                siren_vajsh(HP,level,maidenkiss,eventcode,MaxHP,levelO,frog,nholevel);
                count2=0;
            }else;
            break;
        case 11:
           mushmario(HP,MaxHP,level,phoenixdown);
           break;
        case 12:
            mushfibo(HP);
            break;
        case 15:
            remedy += remedy<99?1:0;
            break;
        case 16:
            maidenkiss += maidenkiss<99?1:0;
            break;
        case 17:
            phoenixdown+=phoenixdown<99?1:0;
            break;
        case 18:
            if(count_18==0){
                merlin(file_merlin_pack,HP,MaxHP);
                count_18=1;
            }
            break;
        case 19:
            if(count_19==0){
                Asclepius(file_aclepius_pack,remedy,maidenkiss,phoenixdown);
                count_19=1;
            }
            break;
        case 99:
            browser(HP,level,rescue);
            level = level>10?10:level;
            break;
        default:
            MushGhost(file_mush_ghost,eventcode,HP,MaxHP,phoenixdown,rescue);
            break;
        }
        // dem luot khi thanh tihon or frog
        if(small==1) {
            if(const_remedy>=1 && remedy>=1){
                HP = nhoHP;
                small=0;
                remedy-=1;
            }
            else if(const_remedy==0 && remedy>0){
                HP*=5;
                HP=HP>MaxHP?MaxHP:HP;
                remedy-=1;
                small=0;
            }else time_small(small,phoenixdown,HP,MaxHP,count1);
        }else if(frog==1){
            if(maidenkiss>=1){
                level=nholevel;
                maidenkiss-=1;
                frog=0;
            }else time_frog(frog,level,phoenixdown,count2,nholevel);
        }
        display(HP,level,remedy,maidenkiss,phoenixdown,rescue); // hien thi thong tin
    }while (rescue==-1 && stmap<=distmap);

    delete[] map; //xoa con tro map
}
void read_file(string file_input, string &mapcode, string &namefile,int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown){
    ifstream file(file_input);
    file>>HP>>level>>remedy>>maidenkiss>>phoenixdown;
   while (!file.eof())
   {
    getline(file,namefile);
    getline(file,mapcode);
   }
   file.close();
}
void xulyfile(string mapcode, int *map,int &distmap){
    istringstream iss(mapcode);
    int n;
    int i = 0;
    while (iss >> n) {
        map[i] = n;
        i++;
    }
    distmap=i;
}
void split_namefile(string namefile,string &file_mush_ghost,string &file_merlin_pack,string &file_aclepius_pack){
    istringstream ss(namefile);
    getline(ss, file_mush_ghost, ',');
    getline(ss, file_aclepius_pack, ',');
    getline(ss, file_merlin_pack, ',');
}
void levelboss(int &levelO, int i){ // level cua boss
    int b = i%10;
    levelO = i > 6?(b > 5?b : 5) : b;
}
void event1to5(int& HP, int& level,int& phoenixdown, int& rescue, int eventCode, int MaxHP,int levelO,int &small,int &frog){
    float damage,basedamage;
    if(king_arthur(MaxHP)==1 || lancelot(MaxHP)==1){
        level += 1;
        level = level>10?10:level;
    }else{
        if (level>levelO) {
            level += 1;
            level = level>10?10:level;
        }
        else if (level==levelO){} //hoa se khong lam gi
        else{
            switch(eventCode){
                        case 1: basedamage=1;
                        break;
                        case 2: basedamage=1.5;
                        break;
                        case 3: basedamage=4.5;
                        break;
                        case 4: basedamage = 7.5;
                        break;
                        case 5: basedamage=9.5;
                        break;
            }
            damage = basedamage * levelO * 10;
            HP = HP - damage;
            if(HP<=0){
                if(phoenixdown>=1){
                    HP=MaxHP;
                    phoenixdown-=1;
                    frog=0;
                    small=0;
                }else rescue=0; 
            }
        }
    }

}
void endgame(int &rescue, int HP, int stmap, int distmap){
    if(stmap>=distmap && HP>0) rescue =1;
    else if(stmap<=distmap && HP>0) rescue=-1;
}
void shaman(int& HP, int& level,int& remedy, int eventCode, int MaxHP,int levelO,int &small, int const_remedy){
    int nhoHP=HP;
    if(king_arthur(MaxHP)==1 || lancelot(MaxHP)==1){
        level += 2;
        level = level>10?10:level;
    }else{
        if (level>levelO) {
            level += 2;
            level = level>10?10:level; 
        }
        else if (level==levelO){} //hoa se khong lam gi
        else tihon(HP,nhoHP,remedy,small,const_remedy); // thua --> ti hon
    }
    
}
void tihon(int &HP, int nhoHP, int &remedy, int &small, int const_remedy){
    small=1;
    if(HP<5) HP=1;
    else HP*=0.2;
    if(const_remedy>=1 && remedy>=1){
        HP = nhoHP;
    }
    else if(const_remedy==0 && remedy>0){
        HP*=5;
        remedy-=1;
        small=0;
    }
}
void time_small(int &small,int &phoenixdown, int &HP, int MaxHP,int &count1){
    if(small=1 && count1<=3){
        count1+=1;
    
        if(count1==4 && small==1){
            if(HP>0){
                HP*=5;
                HP=HP>MaxHP?MaxHP:HP;
            }
            small=0;
            count1 = 0;
        }
        if(small==1 && HP<=0){
            if(phoenixdown>=1){
                phoenixdown-=1;
                small=0;
                HP=MaxHP;
            }
        }
    }else if(small==0) count1=0;
}
void siren_vajsh(int HP,int& level,int& maidenkiss, int eventCode, int MaxHP,int levelO,int &frog, int &nholevel){
    if(king_arthur(MaxHP)==1 || lancelot(MaxHP)==1){
        level += 2;
        level = level>10?10:level;
    }else{
        if (level>levelO) {
            level += 2;
            level = level>10?10:level; 
        }
        else if (level==levelO){} //hoa se khong lam gi
        else in_frog(level,maidenkiss,frog, nholevel); // thua --> frog
    }
}
void in_frog(int &level,int &maidenkiss, int &frog, int &nholevel){
    frog=1;
    nholevel = level;
    level = 1;
}
void time_frog(int &frog,int &level,int &phoenixdown,int &count2,int nholevel){
    if(frog==1 && count2<=3){
        count2+=1;
        if(count2==4 && frog ==1){
            level=nholevel;
            frog=0;
            count2=0;
        }
    }
}
void mushmario(int &HP, int MaxHP, int level, int phoenixdown){
    int s1=0;
    int n1 = ((level + phoenixdown)%5 + 1) * 3;
    int a[15];
    a[0]=99;
    for(int i=0;i<n1;i++){
        if(a[i]>10 && a[i]<100) s1+=a[i];
        a[i+1]=a[i]-2;
    }
    HP = HP + (s1%100) + 1;
    while (!nguyenTo(HP)) {
        HP++;
    }
    HP=HP>MaxHP?MaxHP:HP;
}
void mushfibo(int &HP){
    if (HP > 1) {
        int n = 0;
        while (fibonacci(n) < HP) {
            n++;
        }
        int new_HP = fibonacci(n-1);
        HP = new_HP;
    }
}
int king_arthur(int MaxHP){
    if(MaxHP==999) return 1;
    else return 0;
}
int lancelot(int MaxHP){
    if(nguyenTo(MaxHP)==1) return 1;
    else return 0;
}
// kiem tra va tim snt, fibonaci
int nguyenTo(int n) {
    if (n < 2) return 0;
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}
int fibonacci(int n) {
    if (n <= 1) {
        return n;
    }
    return fibonacci(n-1) + fibonacci(n-2);
}
//------------------
void browser(int HP, int &level, int &rescue){
    if(king_arthur(HP)==1 || (lancelot(HP)==1 && level >=8) || level==10) level=10;
    else rescue=0;
}
void MushGhost(string file_mush_ghost,int eventcode,int &HP,int MaxHP, int &phoenixdown,int &rescue){
    string ms= to_string(eventcode);
    int len = ms.length();
    // xu li file mush_ghost
    ifstream fmg(file_mush_ghost);
    int n2;
    fmg >> n2; // đọc số lượng phần tử từ dòng đầu tiên của file
    int arr[1000], arr2[1000];
    for (int i = 0; i < n2; i++) {
        fmg >> arr[i]; // đọc giá trị từng phần tử vào mảng
        char comma; // bỏ qua dấu ","
        fmg >> comma;
    }

    fmg.close(); // đóng file
    for(int i=0;i<n2;i++){
        if(arr[i]<0) arr2[i] = (17 *arr[i]*-1+9)%257;
        else arr2[i] = (17 *arr[i]+9)%257; 
    }  
    //---------------
        int stcode=2;
    do{   
        if(ms[stcode]=='1'){
            mush_ghost_1(arr,n2,HP);
            HP=HP>MaxHP?MaxHP:HP;
            if(HP<=0){
                if(phoenixdown>0) {
                    HP=MaxHP;
                    phoenixdown-=1;
                }else{
                    rescue=0;
                    break;
                }
            }
        }
        else if(ms[stcode]=='2'){
            mush_ghost_2(arr,n2,HP);
            HP=HP>MaxHP?MaxHP:HP;
            if(HP<=0){
                if(phoenixdown>0) {
                    HP=MaxHP;
                    phoenixdown-=1;
                }else{
                    rescue=0;
                    break;
                }
            }
        }else if(ms[stcode]=='3'){
            mush_ghost_3(arr2,n2,HP);
            HP=HP>MaxHP?MaxHP:HP;
            if(HP<=0){
                if(phoenixdown>0) {
                    HP=MaxHP;
                    phoenixdown-=1;
                }else{
                    rescue=0;
                    break;
                }
            }
        }else if(ms[stcode]=='4'){
            mush_ghost_4(arr2,n2,HP);
            HP=HP>MaxHP?MaxHP:HP;
            if(HP<=0){
                if(phoenixdown>0) {
                    HP=MaxHP;
                    phoenixdown-=1;
                }else{
                    rescue=0;
                    break;
                }
            }
        }
        stcode+=1;
    } while (stcode<len);
}
void mush_ghost_1(int arr[],int n2,int &HP){
    int maxi,mini;
    int max=arr[0],min=arr[0];
    for(int i=0;i<n2;i++){
        if(arr[i]>=max){
            max=arr[i];
            maxi=i;
        }
        if(arr[i]<=min){
            min=arr[i];
            mini=i;
        }
    }
    HP=HP-(maxi+mini);
}
void mush_ghost_2(int arr[],int n2,int &HP){
    int mtx=-2,mti=-3;
    int max=arr[0], maxpos=0;
    bool left=true,right=true;
    if(n2<2){
        mtx=arr[0];
        mti=0;
    }else {
        for(int i=0;i<n2;i++){
            if(arr[i]>max){
                max=arr[i];
                maxpos=i;
            }
        }
        for(int i=1;i<=maxpos;i++){
            if(arr[i]<=arr[i-1]){
                left=false;
                break;
            }
        }
        for(int i=maxpos+1;i<n2;i++){
            if(arr[i]>=arr[i-1]){
                right=false;
                break;
            }
        }
        if(left && right){
            mtx=max;
            mti=maxpos;
        }
    }
    HP = HP - (mtx + mti);
}
void mush_ghost_3(int arr2[],int n2,int &HP){
    int maxi2,mini2;
    int max=arr2[0],min=arr2[0];
    for(int i=0;i<n2;i++){
        if(arr2[i]>=max){
            max=arr2[i];
        }
        if(arr2[i]<=min){
            min=arr2[i];
        }
    }
    for(int i=0;i<n2;i++){
        if(arr2[i]==max){
            maxi2=i;
            break;
        }
    }
    for(int i=0;i<n2;i++){
        if(arr2[i]==min){
             mini2=i;
             break;
        }
    }
    HP = HP - (maxi2 + mini2);
}
void mush_ghost_4(int arr2[],int n2,int &HP){
    int max2_3x,max2_3i;
    if(n2<2 || (n2==2 && arr2[0]==arr2[1])){
        max2_3x =-5;
        max2_3i=-7;
    }else {
        int temp[]={arr2[0],arr2[1],arr2[2]};
        for(int i=0;i<2;i++){
            for(int j=i+1;j<3;j++){
                if(temp[i]>temp[j]){
                    int c=temp[j];
                    temp[j]=temp[i];
                    temp[i]=c;
                }
            }
        }
        for(int i=1;i>=0;i--){
            if(temp[i]!=temp[2]){
                max2_3x=temp[i];
                break;
            }else{
                max2_3x=-5;
                max2_3i=-7;
            }
        }
        for(int i=0;i<3;i++){
            if(arr2[i]==max2_3x){
                max2_3i=i;
                break;
            }
        }
    }
    HP = HP - (max2_3x + max2_3i);
}
void Asclepius(string file_aclepius_pack, int &remedy, int &maidenkiss, int &phoenixdown){
    int arr[50][50];
    int r1,c1;
    ifstream fap(file_aclepius_pack);
    fap>>r1>>c1;
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c1; j++) {
            fap >> arr[i][j];
        }
    }
    fap.close();
    for (int i = 0; i < r1; i++) {
        int counter=0;
        for (int j = 0; j < c1; j++){
            if(arr[i][j]==16){
                remedy += remedy>=99?0:1;
                counter+=1;
            }
            else if(arr[i][j]==17){
                maidenkiss+=maidenkiss>=99?0:1;
                counter+=1;
            }
            else if(arr[i][j]==18){
                phoenixdown+=phoenixdown>=99?0:1;
                counter+=1;
            }
            if(counter==3) break;
        }
    }
    
}
void merlin(string file_merlin_pack, int &HP, int MaxHP){
    int n9;
    ifstream fml(file_merlin_pack);
    fml>>n9;
    string merlin_name = "merlin"; // chuỗi tên của Merlin
    for (int i = 0; i < n9; i++) {
        string item_name;
        fml >> item_name;
        int length = item_name.length();
        for (int i = 0; i < length; i++) {
            item_name[i] = tolower(item_name[i]);
        }
        if(check_pack(merlin_name,item_name)==true){
            if (item_name.find("merlin") != string::npos) HP+=3;
            else HP+=2;
            HP = HP>MaxHP?MaxHP:HP;
        }

    }
    fml.close();
}
bool check_pack(string merlin_name, string item_name){
    int count=0;
    for(int i=0;i<merlin_name.length();i++){
        for(int j=0;j<item_name.length();j++){
            if(merlin_name[i]==item_name[j]){
                count+=1;
                break;
            }
        }
    }
    if(count==6) return true;
    else return false;
}
