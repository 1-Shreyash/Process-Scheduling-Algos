#include <stdio.h> //for sjf
#include <stdlib.h>
#include <set>
#include <iostream>
using namespace std;

struct process
{
    int bt, at, id;
};
struct gantt{
    int prid, toa, endt;//time of arrival
};
int findMinAt(struct process pr[], set<int> remaining)
{
    int atMin = 100;
    for (int i : remaining)
    {
        if (atMin > pr[i].at)
            atMin = pr[i].at;
    }
    // cout<<"hs"<<endl;
    return atMin;
}
int findMinBtindex(struct process pr[], set<int> arrived)
{
    int btMin = *(arrived.begin());
    // cout << endl;
    for (int i : arrived)
    {
        // cout << pr[i].id << " ";
        if (pr[btMin].bt > pr[i].bt)
            btMin = i;
    }
    // cout << endl;
    return btMin;
}
void update(set<int> &remaining, set<int> &arrived, struct process pr[], int t){
    if (remaining.empty() == false)
        {
            for (int i : remaining)
            {
                // cout << "me" << endl;
                if (pr[i].at <= t)
                {
                    arrived.insert(i);
                    // cout << "\t arrived:" << pr2[i].id << endl;
                }
            }
            for (int i : arrived)
            {
                remaining.erase(i);
            }
        }
}
int main()
{
    struct process pr[10];
    struct process pr2[10];
    vector<struct gantt> g;
    set<int> remaining;
    set<int> arrived;
    set<int> done;
    rand();
    for (int i = 0; i < 10; i++)
    {
        int a;
        while ((a = rand() % 20) == 0);
        pr[i].bt = a;
        pr[i].at = rand() % 10;
        pr[i].id = i;

        pr2[i] = pr[i];
    }

    // sorting pr according to the
    cout<<"<------------------FCFS ALGO------------------>\n\n";
    printf("Process\tBT\tAT\n");
    for (int i = 0; i < 10; i++)
    {
        printf("P%d\t%d \t%d\n", pr[i].id, pr[i].bt, pr[i].at);
        // printf("hes\n");
    }

    // sorting the processes with respect to at
    struct process temp;
    for (int i = 1; i < 10; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (pr2[i].at < pr2[j].at)
            {
                temp = pr2[i];
                pr2[i] = pr2[j];
                pr2[j] = temp;
            }
            if(pr2[i].at == pr2[j].at){
                if(pr2[i].id < pr2[j].id){
                    temp = pr2[i];
                    pr2[i] = pr2[j];
                    pr2[j] = temp;
                }
            }
        }
    }
    // printf("\nProcess\tBT\tAT\n");
    // for (int i = 0; i < 10; i++)
    // {
    //     printf("P%d\t%d \t%d\n", pr2[i].id, pr2[i].bt, pr2[i].at);
    //     // printf("hes\n");
    // }
    for(struct process p: pr2)
        remaining.insert(p.id);
    int t;
    int j;
    // function starts

    while (arrived.empty() == false || remaining.empty() == false)
    {
        // cout << "hello" << endl;
        if (arrived.empty() == true && remaining.empty() == false)
            t = findMinAt(pr2, remaining);
        // cout << "T : " << t << endl;
        update(remaining, arrived, pr2, t);
        if (arrived.empty() == false)
        {
            j = *arrived.begin();

            struct gantt g1;
            g1.prid = pr2[j].id;
            g1.toa = t;
            arrived.erase(j);
            t += pr2[j].bt;

            // cout << "t:" << t << endl;
            update(remaining, arrived, pr2, t);
            done.insert(j);
            g1.endt = t;
            g.push_back(g1);
            // cout << pr2[j].id << endl;
        }
    }
    cout<<endl;
    cout<<"******** Gantt Chart: ********\n";
    // cout<<"\tTOA\t"<<"Process"<<endl;
    cout<<"-----------------------------------------------------------------------\n";
    cout<<"|";
    for(struct gantt s : g){
        cout<< "  P" << s.prid <<"  |";
    }
    cout<<endl;
    cout<<"-----------------------------------------------------------------------\n";
    cout<<"\nProcess\tTAT\tWT\n";
    int totalTAT = 0; 
    int totalWT = 0;
    for(struct gantt s: g){
        int tat = s.endt - pr[s.prid].at;
        int wt = tat - pr[s.prid].bt;
        cout<<"P"<<s.prid<<"\t"<< tat <<"\t"<< wt <<endl;
        totalTAT += tat;
        totalWT += wt;
    }
    cout<<"\nAvg TAT = "<<totalTAT/10.0<<"\t"<<"Avg WT = "<<totalWT/10.0<<endl;
    cout<<"\n<--------------------END-------------------->\n\n";
    return 0;
}