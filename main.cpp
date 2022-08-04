#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//クラス「ポケットマネーブック」
struct PocketMoneyBook{
    string date;//日付＝データメンバdateで管理
    string item;//摘要＝データメンバitemで管理
    int income;//収入＝データメンバincomeで管理
    int expense;//支出＝データメンバexpenseで管理

    void setDate(string newDate);
    void setItem(string newItem);
    void setIncome(int newIncome);
    void setExpense(int newExpense);
    void show();//表示関数
};
//関数の定義
void PocketMoneyBook::setDate(string newDate){
    date = newDate;
}
void PocketMoneyBook::setItem(string newItem){
    item = newItem;
}
void PocketMoneyBook::setIncome(int newIncome){
    income = newIncome;
}
void PocketMoneyBook::setExpense(int newExpense){
    expense = newExpense;
}
void PocketMoneyBook::show(){
    cout << "日付：" << date << "\t摘要：" << item << "\t収入：" << income << "円" << "\t支出：" <<  expense << "円" << endl;
}

bool operator<(const PocketMoneyBook& lhs, const PocketMoneyBook& rhs){
    return lhs.expense > rhs.expense;
}//出費が多い順番に並べるための演算子

void starting(){
    cout << "テキストデータの準備はよろしいですか？" << endl;
    cout << "プログラムを開始する際は「a」を打ってからEnterを押してください。" << endl;
    string key;
    cin >> key;
    if (key == "a"){
        cout << "お小遣い帳" << endl;
    }
}//プログラム開始時の確認に使う関数


int main(){
    vector<PocketMoneyBook> PMBVec;
    
    starting();
    ifstream infile("shoppingdata.txt");
    
    
    string date;
    string item;
    int income;
    int expense;
    int allincome = 0;
    int allexpense = 0;
    int nowbalance = 0;
    while(infile >> date >> item >> income >> expense){
        PMBVec.emplace_back();
        PMBVec[PMBVec.size() -1].setDate(date);
        PMBVec[PMBVec.size() -1].setItem(item);
        PMBVec[PMBVec.size() -1].setIncome(income);
        PMBVec[PMBVec.size() -1].setExpense(expense);
        
        allincome += int(income);
        allexpense += int(expense);
        nowbalance += int(income - expense);
        
    }
    
    infile.close();
    
    for (int i = 0; i < PMBVec.size(); i++)PMBVec[i].show();
    
    cout << endl;
    cout << "総収入" << allincome << "円" << "\t総支出" << allexpense << "円" << endl;
    cout << "現在の残高" << nowbalance << "円" << endl;
    
    sort(PMBVec.begin(), PMBVec.end());//イテレータで支出が大きい順に並べる
    cout << "これまでで出費が最も大きいものは" << endl;
    cout << PMBVec[0].item << "(" << PMBVec[0].expense << "円" << ")" << "です。無駄遣いに気をつけよう！" << endl;
}
