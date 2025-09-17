//Yi Feng Huang G01532343

#include <stdio.h>
#include <string.h>
#define MAX_LEN 25
#define INSERTNUMBER 10

//Global variables 全域變數
char str[INSERTNUMBER][MAX_LEN+1]; //array to store 10 strings

//1.check if input is verify 確認輸入資料
int checkdata(const char *input, int current)
{
    // check if input is NULL 檢查是否為空字串
    if(input[0] == '\0') {
        printf("\033[31m value cannot be empty \033[0m\n");
        return 0;
    }
    // check if input are ' ' only 檢查字串是否全是空白
    int not_all_space = 0; //flag to check all space
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] != ' ') {
            not_all_space = 1; //not all space
            break;
        }
    }
    if (!not_all_space) {
        //printf("[DEBUG] checkdata: input is all spaces\n");
        printf("\033[31m value cannot be all spaces \033[0m\n");
        return 0;
    }
    if(input[0])
    //check  length exceed MAX_LEN 檢查長度
    if(strlen(input) > MAX_LEN){
        //printf("[DEBUG] checkdata: input too long, length=%zu\n", strlen(input));
        printf("\033[31m value need to be less than 25 string \033[0m \n");
        return 0;
    }
    //check for duplicate 檢查是否重複
    for (int j = 0; j<current; j++) {
        if (strcmp(input, str[j]) == 0) {
            //printf("[DEBUG] checkdata: duplicate with str[%d]='%s'\n", j, str[j]);
            printf("\033[31m duplicate string – please re-enter \033[0m \n");
            return 0;
        }
    }
    //check data is illegal character, not include + $ % ^ () 檢查是否有非法字元
    for (int i = 0; input[i]!= '\0' ; i++) {
        if ((input[i] == '+' || input[i] == '$' || input[i] == '%' || input[i] == '^' || input[i] == '(' || input[i] == ')')) {
            //printf("[DEBUG] checkdata: illegal char '%c' at pos %d\n", input[i], i);
            printf("\033[31m illegal character '%c' – please re-enter \033[0m \n",input[i]);
            return 0;
        }   
    }
    //if all check passed, store the valid input 
    return 1;
}

//2.insert 輸入
void insert(void)
{
        char instr[MAX_LEN+2]; //input string 
        //fgets mostly will read up to MAX_LEN-1 (i.e. 24) characters, and the last position is automatically filled with the string terminator \0.
        //fgets 最多會讀取到 MAX_LEN-1 (即 24) 個字元，最後一個位置自動填入字串終止符號 \0。
        //we need one more space for the newline character \n, so we use instr[MAX_LEN+2]
        //我們需要多一個空間來存放換行符號 \n，所以我們使用 instr[MAX_LEN+2]
        for (int i = 0; i < INSERTNUMBER; i++) {

            printf("\033[32m Enter string %d: \033[0m", i+1);
            
            // Read input with fgets 使用fgets讀取輸入 fgets(字元陣列, 陣列大小, 輸入來源);
            
            if (fgets(instr, sizeof(instr), stdin) == NULL) {
                printf("\033[31m Input error, please re-enter. \033[0m\n");
                i--;
                continue;   // Decrement i to repeat this iteration 重複輸入原本的
                            //continue; 只會跳過本次迴圈剩下的程式碼，然後進入下一輪，但 for 迴圈的 i++ 還是會執行。
            }

            // check for buffer overflow 檢查是否有超過緩衝區（即沒讀到換行符號）
            if (strchr(instr, '\n') == NULL) {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF); //get all characters until newline or EOF 清空緩衝區
            }

            // Remove newline character if present 移除換行符號
            instr[strcspn(instr, "\n")] = 0; 

            //data validation 資料驗證
            if(checkdata(instr,i)==1){
                strcpy(str[i], instr);
            } else {
                i--; // Decrement i to repeat this iteration 重複輸入原本的

            };
        }
}

//3.sort verify 排序輸入確認
int sort_datacheck(const char *order){
    if(strcmp(order, "A") == 0 || strcmp(order, "D") == 0){
        return 1;
    } else {
        printf("\033[31m Invalid input,re-enter order. \033[0m\n");
        return 0;
    }
}

//4.sort array by insert 'A' or 'D' 排序 by 'A' or 'D' (bobble sort)
char sort(void)
{
    char order[3]; //order rule 排列規則暫存
    //排序規則設定
    printf("\033[32m Print character strings in Ascending or Descending order: \033[0m\n");
    while(1){
        printf("\033[32m Enter 'A' for Ascending or 'D' for Descending: \033[0m");
        //讀取輸入
        fgets(order, sizeof(order), stdin);
        // Check for buffer overflow 檢查是否有超過緩衝區（即沒讀到換行符號）
        if (strchr(order, '\n') == NULL) {
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF); //get all characters until newline or EOF 清空緩衝區
        }
        // Remove newline character if present 移除換行符號
        order[strcspn(order, "\n")] = 0;
        
        //data validation 資料驗證
        if(sort_datacheck(order)==1){
            break;
        }
    }

    //printf("[DEBUG] sort: order='%s'\n", order);
    //printf("[DEBUG] sort: before sort, str[] =\n");
    //    for (int k = 0; k < INSERTNUMBER; k++) {
    //        printf("[DEBUG] str[%d]='%s'\n", k, str[k]);
    //    }
    char temp[MAX_LEN+1];//temp variable for swap 交換用暫存變數
    // sort by selection sort method 使用選擇排序法
    for (int i = 0; i < INSERTNUMBER - 1; i++) {
        //printf("[DEBUG] str[%d]='%s'\n", i, str[i]);
        for (int j = i + 1; j < INSERTNUMBER; j++) {
            //strcmp int strcmp(const char *s1, const char *s2); 
                //如果 s1 和 s2 完全一樣，回傳 0
                //如果 s1 在字典順序小於 s2，回傳負數
                //如果 s1 在字典順序大於 s2，回傳正數
            if ((order[0] == 'A' && strcmp(str[i], str[j]) > 0) || (order[0] == 'D' && strcmp(str[i], str[j]) < 0)) {
                // Swap elements
                //printf("[DEBUG] swap: str[%d]='%s' <-> str[%d]='%s'\n", i, str[i], j, str[j]);
                strcpy(temp, str[i]); 
                strcpy(str[i], str[j]);
                strcpy(str[j], temp);
            }
        }
    }

    //printf("[DEBUG] sort: sorted finish\n");
    // print sorting order 列印排序方式
    if(order[0] == 'A'){
        printf("\033[32m Ascending order: \033[0m\n");
    } else if (order[0] == 'D'){
        printf("\033[32m Descending order: \033[0m\n");
    }
    return order[0];
}

//5.print result 列印結果
void print(char order)
{
    //print all strings 列印所有字串
    printf("\033[32m The strings you entered are: \033[0m\n");
    for (int i = 0; i < INSERTNUMBER; i++) {
        printf(" \t %d-> \t %s\n",i+1, str[i]);
    }
    //print lowest and highest ascii value 列印最高和最低的字串
    if(order == 'A'){
        printf("\033[32m String with lowest ascii value: %s \033[0m\n", str[0]);
        printf("\033[32m String with highest ascii value: %s \033[0m\n", str[INSERTNUMBER - 1]);
    } else {
        printf("\033[32m String with lowest ascii value: %s \033[0m\n", str[INSERTNUMBER - 1]);
        printf("\033[32m String with highest ascii value: %s \033[0m\n", str[0]);
    }   
}

int main(void)
{
    char order ; //order rule
    //start 開始
    printf("\033[32m Enter %d character strings: \033[0m \n", INSERTNUMBER); 
    //insert 輸入
    //printf("[DEBUG] main: start insert\n");
    insert();
    //sort 排序
    //printf("[DEBUG] main: start sort\n");
    order=sort();
    //printArray 列印
    //printf("[DEBUG] main: start print\n");
    print(order);
    return 0;
}
