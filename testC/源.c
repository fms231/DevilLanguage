#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>

//����ջ
typedef struct stack
{
	char data;//����
	struct stack* next;//ָ��
}stack;

//ʹ����ʽ�洢��ʽ
//����ʵ��
void push(stack* top, char data);//ѹջ
char pop(stack* top);//����ջ��Ԫ�ز�����
stack* mowang(stack* top);//�����Ĺؼ����裬ħ�����Եķ���
void printstack(stack* top);//��ӡջ�е�Ԫ��
stack* upsidedown(stack* top);//����ջ
int check(stack* top);//���ħ�������Ƿ������

//ѹջ
void push(stack* top, char data)
{
	stack* newstack = (stack*)malloc(sizeof(stack));
	newstack->data = data;
	newstack->next = top->next;
	top->next = newstack;
	top->data++;
}
//����ջ��������ջ��Ԫ��
char pop(stack* top)
{
	if (top->next == NULL)
		return 0;
	else
	{
		stack* temp;
		temp = top->next;
		top->next = temp->next;
		char data = temp->data;
		temp->next = NULL;
		//�ͷ��Ѿ�������ڴ�ռ�
		free(temp);
		return data;
	}	
}
//�����Ĺؼ����裬���ʵ��ħ������
stack* mowang(stack* top)
{
	//�����˴η����Ľ��ջ
	stack* result_top = (stack*)malloc(sizeof(stack));
	result_top->next = NULL;
	//���β鿴ջ�е�����Ԫ��
	while (top->next)
	{
		char flag = pop(top);
		//�鿴ջ��Ԫ�ض�Ӧ��ħ������
		if (flag == 'A')
		{
			push(result_top, 'e');
			push(result_top, 'a');
			push(result_top, 's');
		}
		else if (flag == 'B')
		{
			push(result_top, 'A');
			push(result_top, 'd');
			push(result_top, 'A');
			push(result_top, 't');
		}
		else if (flag == ')')
		{
			stack* p = top;
			int number = 0;
			//���ҵ���ǰ��Ԫ��
			while (p->next->data != '('&&p->next)
			{
				p = p->next;
				number++;
			}
			//�����������Ԫ��
			if (number != 0)
			{
				char* assemble = (char*)malloc(number*sizeof(char));
				int i = number;
				//�������е�Ԫ�ص������η���������
				while (top->next->data != '(')
				{
					assemble[--i] = pop(top);
				}
				//�������е�Ԫ�ذ���ħ�����Եķ���������η�����һ��ջ��
				for (i = 0; i < number - 1; i++)
				{
					push(result_top, assemble[0]);
					push(result_top, assemble[i + 1]);
				}
				push(result_top, assemble[0]);
				char temp = pop(top);
			}
		}
		else
		{
			push(result_top, flag);
		}
	}
	return result_top;
}
//��ӡջ��Ԫ��
void printstack(stack* top)
{
	stack* temp = top->next;
	while (temp)
	{
		printf("%c", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
//����ջ�ĵ�Ԫ��
stack* upsidedown(stack* top)
{
	stack* p = top->next;
	stack* q = NULL, * pr = NULL;
	top->next = NULL;
	while (p)
	{
		pr = p->next;
		p->next = q;
		q = p;
		p = pr;
	}
	top->next = q;
	return top;
}
//����Ƿ�����ħ�����Զ��ѷ��룬���򷵻�1�������򷵻�0
int check(stack* top)
{
	stack* p = top->next;
	while(p)
	{
		if (p->data == 'A' || p->data == 'B')
		{
			return 0;
		}
		p = p->next;
	}
	return 1;
}

int main()
{
	stack* top = (stack*)malloc(sizeof(stack));
	top->next = NULL;
	char input;
	int i;
	printf("������ħ�����ԣ�\n");
	while(scanf("%c",&input)!=EOF)
	{
		push(top, input);
	}	
	stack* result = mowang(top);
	//����ջ����ʵ��
	while (!check(result))
	{
		result = upsidedown(result);
		result = mowang(result);	
	}
	printstack(result);
}
