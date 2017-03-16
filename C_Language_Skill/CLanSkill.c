/*
*日期：2017.3.16
*/


/*
定义指向函数的指针类型
*/
typedef int ( *SENDFUC )( unsigned char *pSendData, unsigned char ucLen );


/*
枚举类型定义
*/
typedef enum _RDDIR{

	RDDIR_N,
	
	RDDIR_H,
	
}RDDIR;      //重定义枚举类型


/*
通用结构体定义
包含各种类型的数据，指针，和指向函数的指针（操作数据的方法）
*/
typedef struct _tagControllerMain{

	pMSCUController     pSCUControll;          //结构体类型数据
	
	void *				GroupCmdTimer;         //void类型指针
    
	unsigned char       curbRedFlash;          //8位长数据
	
	unsigned short      curWorkChin;           //16位长数据

	SENDFUC				pCommunicationFuc;     //指向函数的指针
	
}ControllerMain,*pControllerMain;              //重定义结构体类型，重定义结构体类型指针


/*
宏定义
参数 A 指向函数的指针，或A是结构体指针
参数 B C 函数的参数
用法：当A指针不为空指针时，执行A所指向的函数
*/
#define Send_Fuc( A, B , C )	(	( (A) == NULL )?NULL:((A)(B,C) ) )

/*
宏定义
用法：当参数A是指向结构体的指针时
*/
#define Send_ManMachineButtonsPanelComm( A,B,C ) Send_Fuc( (A)->pSendManMachineButtonsPanelCommFuc, B, C )


/*
宏定义
参数 A 数据
参数 B 数据的第几位
用法：查询数据第B位的值；设置数据第B位为1；清除数据的第B位为0
*/
#define GET_NETADDRSTATE( A, B )	( ( ( A ) >> ( B ) ) & 0x01 )
#define SET_NETADDRSTATE( A, B )	( A ) |=  ( 1 << ( B ) )
#define CLER_NETADDRSTATE( A, B )	( A ) &= ~( 1 << ( B ) )
