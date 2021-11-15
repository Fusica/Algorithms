/**
 * @Author: Max
 * @Time: 10/23/21 13:11
 */

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;



//Check type of sentence
int judge_symbol(string main_str, int &i){
    int pos;
    if(main_str.find("{", i) == i)
        pos = 1;
    else if(main_str.find("if", i) == i && (main_str[i+2]==' ' || main_str[i+2]=='('))
        pos = 2;
    else if(main_str.find("for", i) == i && (main_str[i+3]==' ' || main_str[i+3]=='('))
        pos = 3;
    else if(main_str.find("else", i) == i && main_str[i+4]==' ')
        pos = 4;
    else if(main_str.find("while", i) == i && (main_str[i+5]==' ' || main_str[i+5]=='('))
        pos = 5;
    //else if(main_str.find("else if", i) == i && (main_str[i+7]==' ' || main_str[i+7]=='('))
    //    pos = 7;
    else
        pos = 0;   //Normal sentence
    return pos;
}

//pass useless space
void ignore_space(string main_str, int &i){
    while(main_str[i] == ' ')
        i++;
}

//print space
void print_space(int space){
    for(int k=0; k<space; k++)
        cout << " ";
}

int main(){
    string main_str;
    getline(cin, main_str);
    int i=0, space=0, left_space=0, j, m, index, k, tmp;  //k store terminal parameter for pos of i
    bool flag;

    //deal by order, print while judge
    ignore_space(main_str, i);  //Ignore extra space

    index = main_str.find(')', 0);  //output "int main()"
    for(j=i; j<=index; j++)
        printf("%c", main_str[j]);
    cout << "\n{\n";
    space += 2;
    i = index+1;
    ignore_space(main_str, i);
    i++;

    while(i < main_str.length()){
        ignore_space(main_str, i);
        tmp = judge_symbol(main_str, i);
        if(tmp != 0){
            print_space(space);  //Output space first

            if(tmp == 1){
                cout << "{\n";
                i++;
                space += 2;
                continue;
            }
            //else: special case
            if(tmp == 4){
                for(j=0; j<4; j++)
                    cout << main_str[i+j];
                k = i+3;
            }
            else{
                for(j=0; j<tmp; j++)
                    cout << main_str[i+j];
                cout << " ";
                i += tmp;
                ignore_space(main_str, i);

                k = i;

                //用t来判断if，while，for的括号中语句结束
                int t=0;
                while(1){
                    if(main_str[k] == '('){
                        t++;
                    }
                    else if(main_str[k] == ')'){
                        t--;
                        if(!t)
                            break;
                    }
                    k++;
                }
                for(j=i; j<=k; j++)
                    cout << main_str[j];
            }
            //find '{'
            m = k+1;
            ignore_space(main_str, m);
            if(main_str[m] == '{'){
                cout << " {\n";
                flag = true;
                i = m+1;  //return current pos to i
            }else{
                cout << " {\n";
                flag = false;
                left_space++;
                i = m;
            }
            space += 2;
        }
        else if(main_str[i] == '}'){
            space -= 2;
            print_space(space);
            cout << "}\n";
            if(space == 0)
                break;
            i++;

            ignore_space(main_str, i);
            while(left_space != 0 && judge_symbol(main_str, i) != 4){
                space -= 2;
                print_space(space);
                cout << "}\n";
                left_space--;
            }
        }
        else{
            //Normal Sentence
            index = main_str.find(';', i);
            print_space(space);
            for(j=i; j<=index; j++)
                cout << main_str[j];
            cout << "\n";
            i = index+1;
            if(left_space && !flag){
                space -= 2;
                print_space(space);
                cout << "}\n";
                left_space--;

                ignore_space(main_str, i);
                while(left_space && judge_symbol(main_str, i)!=4){
                    space -= 2;
                    left_space--;
                    print_space(space);
                    cout << "}\n";
                }
            }
        }
    }
    return 0;
}
