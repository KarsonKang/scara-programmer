/**********************************
	�A�J�f�~�b�N �X�J�����{�b�g C����T���v��	�y�������W�ϊ��z

	�{�T���v���̃r���h�E���s�ɂ́ACP2110/4 HID USB-to-UART �C���^�[�t�F�[�X���C�u�����@���K�v�ł��B
	SiLabs�Ђ�web�y�[�W(���L)���A�\�t�g�E�F�A�{�̂ƃh�L�������g���_�E�����[�h���APC�ɃC���X�g�[�����Ă��������B
	http://jp.silabs.com/products/interface/Pages/CP2110EK.aspx

	PC�ɃC���X�g�[��������A�{�\�[�X���܂�VisualStudio�̃v���W�F�N�g�̃v���p�e�B���J���A���L�̐ݒ���s���Ă��������B
		1�D�u�\��(C):�v���u���ׂĂ̍\���v�ɕύX
		2�D�u�\���v���p�e�B�v -> �uVC++ �f�B���N�g���v���N���b�N���A�u�C���N���[�h�f�B���N�g���v�ɃC���N���[�h�t�@�C���ւ̃p�X��ǉ�
			�f�t�H���g�̃C���X�g�[���ݒ�ŁuC:\SiLabs\MCU\CP2110_4_SDK\Library\Windows\�v�ɂȂ�܂��B
		
		3�D�������A�u���C�u�����f�B���N�g���v�Ƀ��C�u�����ւ̃p�X��ǉ�
			��L�Őݒ肵���C���N���[�h�t�@�C���̃p�X�Ɂux86�v�ux64�v�̃t�H���_������̂ŁA�v���W�F�N�g�̑Ώۃv���b�g�t�H�[���ɍ��킹�Ăǂ��炩��I�����܂��B
			�v���b�g�t�H�[���̐ݒ�̊m�F�́A�v���W�F�N�g�̃v���p�e�B���J���A�u�v���b�g�t�H�[���v�̍��ڂ��m�F���܂��B
			Visual Studio�̓f�t�H���g�ŁuWin32�v�̐ݒ�ɂȂ��Ă���A���̏ꍇ�́ux86�v�̕����g�p���܂��B
			
		4�D�uOK�v���N���b�N
		5�D�v���O�����̎��s�t�H���_�ɁA�uSLABHIDDevice.dll�v�uSLABHIDtoUART.dll�v�̃t�@�C�����R�s�[
			�u���C�u�����f�B���N�g���v�őI�������t�H���_�̕��̃t�@�C�����g���܂��B


	�ʐM���b�Z�[�W�𑗐M����ƁA�K�����[�J���G�R�[���������܂��B
	���[�^�p�x�����{�b�g��������擾����ꍇ�A���擾�p�̃��b�Z�[�W��PC���瑗�M������A
	ReadLocalEcho�֐��̂悤�Ƀ��[�J���G�R�[��S�ēǂݏo���Ă���A���{�b�g����̕ԐM���b�Z�[�W����M���܂��B

**********************************/
#define	_CRT_SECURE_NO_WARNINGS

/*--------------	�w�b�_�t�@�C��	----------------*/
#include	<Windows.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>

//CP2110/4 HID USB-to-UART �C���^�[�t�F�[�X���C�u�����̃C���N���[�h�t�@�C��
#include	<SLABCP2110.h>
#include	<SLABHIDtoUART.h>
#include	<CP2114_Common.h>

//CP2110/4 HID USB-to-UART �C���^�[�t�F�[�X���C�u���� �ւ̃����N
#pragma	comment(lib,"SLABHIDtoUART.LIB")
#pragma	comment(lib,"winmm.LIB")




/*--------------		�}�N��		----------------*/
/*----	�ʐM�Ɋւ���ݒ�	----*/
//���{�b�g��Vender ID
#define	VID	(0x10C4)

//���{�b�g��Product ID
#define	PID	(0xEA80)


/*----	�{�̂̐��@�Ɋւ���ݒ�	----*/
//���֐߂̎��ԋ����imm�j
#define	AXISLEN_A	(80.0)
//���֐߂̎��ԋ����imm�j
#define	AXISLEN_B	(80.0)

//�X�e�[�W�̏c��(mm)
#define	FIELD_H	(210.0)
//�X�e�[�W�̉���(mm)
#define	FIELD_W	(230.0)
//�X�e�[�W���������_(0,0)�Ƃ����A�A�[���̍����iID1���[�^�̏o�͎��j��X���W(mm)
#define	X_OFS	(FIELD_W/2 - 53.0)

//�㉺���̋������Z�W��
#define	HEIGHT_RATE	(148.54)
//�㉺���̉��͈�(mm)
#define	HEIGHT_RANGE	(35.0)
//���[�^�p�x���狗���ɕϊ�����}�N���֐��Br=���[�^�p�x�l(0.1�x�P��)
#define	RAD_TO_HEIGHT(r)	( ((double)r/(HEIGHT_RATE*10.0))*HEIGHT_RANGE)
//�������烂�[�^�p�x�ɕϊ�����}�N���֐��Bh=����(mm)
#define	HEIGHT_TO_RAD(h)	(short) (h/HEIGHT_RANGE*HEIGHT_RATE*10.0)


//�n���h���̋������Z�W��
#define	WIDTH_RATE	(31.83)
//�n���h���̉��͈�(mm)
#define	WIDTH_RANGE	(5.0*2.0)
//�܂̌��ʒu�̕�(mm)
#define	GROW_W	(5.0*2.0)
//���[�^�p�x���畝�ɕϊ�����}�N���֐��Br=���[�^�p�x�l(0.1�x�P��)�Ap=�܂̎��t���ʒu�i0�`3�j
#define	RAD_TO_WIDTH(r,p)	( ((double)-r/(WIDTH_RATE*10.0))*WIDTH_RANGE + GROW_W*(p+1))
//������T�[�{�p�x�ɕϊ�����}�N���֐��Bw=�܂̕�(mm)�Ap=�܂̎��t���ʒu�i0�`3�j
#define	WIDTH_TO_RAD(w,p)	(short) (-(w-GROW_W*(p+1))/WIDTH_RANGE*WIDTH_RATE*10.0)

//�A�[���̃��[�^�̉��͈́i0.1�x�P�ʁj
#define	ARM_RAD_RANGE	(1350)
//�n���h�J���̃��[�^�̉��͈́i0.1�x�P�ʁj
#define	HAND_WIDTH_RANGE	(350)


/*----	���W�n�Ɋւ���ݒ�	----*/
//�{�̂̊p�x
#define	BASE_ANGLE	(180.0)
//�{�̂̈ʒu(mm)
#define	BASE_OFFSET_X	(+0.0)
#define	BASE_OFFSET_Y	(+0.0)

//���݂̃n���h���̒܂̂˂����ԍ��i0�`3 = �@�`�C�j
#define	CROW_POS	(1)


/*----	���̑��K�v�Ȑݒ�	----*/
//�~����
#define	M_PI	(3.1415926)

//���[�^�̖ڕW�ʒu�ւ̈ړ��ɑ΂���J�ڎ���(msec)
#define	MOVE_TIME	(1000)


/*-------------- �֐��̃v���g�^�C�v�錾 ---------------*/
int RSTorqueOnOff( HID_UART_DEVICE dev, short sMode ,BYTE id,int num);
int RSGetAngle( HID_UART_DEVICE dev ,BYTE id,short *getParam);
int RSMove( HID_UART_DEVICE dev , short *sPoss, unsigned short sTime ,BYTE id,int num);
int ReadLocalEcho(HID_UART_DEVICE dev ,unsigned char *sendbuf,DWORD data_len);
int RSWriteMem( HID_UART_DEVICE dev , BYTE address , BYTE size , BYTE id , BYTE *data , int num);
void pos_to_rad(double x, double y, double z,double yaw, double w,short *sPos,int sign,int num);
int SetTXOpenDrain(HID_UART_DEVICE dev );


/*--------------		����			 ---------------*/
void main()
{
	int servoNum = 0;		//���ݐڑ�����Ă��郂�[�^�̐��i3����=3�A5����=5�j
	DWORD numDevice=0;
	HID_UART_DEVICE dev=0;	//�ʐM�n���h��

	printf("SCARA-Robot sample 'position to motor-axis-param'.\n");

	//����PC�ɐڑ�����Ă��郍�{�b�g�̐����擾
	HidUart_GetNumDevices(&numDevice,VID,PID);
	printf("%d device(s) found.\n",numDevice);

	//����1����ڑ�����Ă��Ȃ�������v���O�������I��
	if(numDevice==0) return;

	//1��ڂ̃��{�b�g�ɐڑ�
	if(HidUart_Open(&dev,0,VID,PID)!=HID_UART_SUCCESS){
		//�����ڑ����������s���Ȃ�������I��
		printf("cannot open device\n");
		return ;
	}
	else{

		//TX �� Open-Drain �ɕύX
		SetTXOpenDrain(dev);


		//������ݒ�B�R���\�[���Ő��l�i3��5�j�����
		do{
			printf("How many motors?(3 or 5):");
			scanf("%d",&servoNum);
			if(servoNum!=3 && servoNum!=5) printf("Does not correspond to %d motors.\n");
			else break;
		}while(1);
		
		printf("%d-axis type\n",servoNum);

		//�`�揈���̊J�n
		//�Q�C����ON
		printf("Gain ON.\n");
		RSTorqueOnOff(dev,1,1,servoNum);

		//���C���������J�n
		while(1){
			short sPos[2];
			double tx,ty,tz,tyaw,tw;	//�ړI���W���擾����ϐ�
			int sign=-1;

			//�ړ���̍��W�����
			printf("Input move positon x:");
			scanf("%lf",&tx);
			printf("Input move positon y:");
			scanf("%lf",&ty);
			printf("Input move positon z:");
			scanf("%lf",&tz);
			if(servoNum>3){
				printf("Input move positon yaw:");
				scanf("%lf",&tyaw);
				printf("Input move positon width:");
				scanf("%lf",&tw);
			}

			//���W�����ɁA�A�[�����iID1,ID2�j�̊p�x�����߂�
			pos_to_rad(tx,ty,tz,tyaw,tw,sPos,sign,servoNum);

			if(servoNum>3) printf("  move to (%lf,%lf,%lf,%lf,%lf)\n",tx,ty,tz,tyaw,tw);
			else printf("  move to (%lf,%lf,%lf)\n",tx,ty,tz);

			for(int i=0;i<servoNum;i++){
				printf("ID%d=%+d ",i,sPos[i]);
			}
			printf("\n");

			//����ꂽ�p�x�ɃA�[���𓮂���
			RSMove(dev,sPos,MOVE_TIME/10,1,servoNum);
			Sleep(MOVE_TIME);

		}

		//�Q�C����OFF
		RSTorqueOnOff(dev,0,1,servoNum);
	}


	//���{�b�g�Ƃ̒ʐM��ؒf
	printf("close device\n");
	HidUart_Close(dev);

}



/************************************************

	void pos_to_rad(double x, double y, double z,double yaw, double w,short *sPos,int sign,int num)
	
	�T�v�F�^����ꂽ�������W�iX/Y/Z�j�ƃn���h���̊p�x�E�J�����A���[�^�̖ڕW�ʒu�ɕϊ�����֐��B

	�����F
		double x,y,z	�c �ϊ�����X/Y/Z���W
		double yaw		�c �ϊ����̃n���h��]���̊p�x
		double w		�c �ϊ����̃n���h�J���̕�
		short sPos		�c �v�Z��̃��[�^�p�x��������z��ϐ��ւ̃|�C���^
		int sign		�c �A�[���̐܂�Ȃ�������B���̒l���Ǝ��v���A���̒l���Ɣ����v���ɐ܂�Ȃ���
		int num			�c �g�p���郂�[�^��

	�߂�l�F
		����

*************************************************/
void pos_to_rad(double x, double y, double z,double yaw, double w,short *sPos,int sign,int num)
{

	double a,b,tx,ty,lx,ly;		//�]���藝�����߂�ϐ�
	double thete1,thete2;		//ID1�AID2�̊p�x�����߂�ϐ�
	double s;					//�A�[���̐܂�Ȃ�������i�����j�Ɏg�p����ϐ��Bint sign�̕����ɉ�����+1.0��-1.0��������

	//�����̕�������A�[���̐܂�Ȃ������������
	if(sign<0) s=-1.0;
	else s=1.0;

	//�{�̂̈ʒu�Ɗp�x�̐ݒ�𔽉f������i�ϊ������t�]�����āA�����E�ʒu����0�̈ʒu����ɂ����l�ɕϊ��j
	lx= x-BASE_OFFSET_X;
	ly= y-BASE_OFFSET_Y;
	x = (lx*cos(-BASE_ANGLE/180.0*M_PI)-ly*sin(-BASE_ANGLE/180.0*M_PI));
	y = (lx*sin(-BASE_ANGLE/180.0*M_PI)+ly*cos(-BASE_ANGLE/180.0*M_PI));

	ty = y;
	tx = x+X_OFS;


	//���������N�����ڕW�l��������΁A�����̎���ڕW�l�܂ł̊p�x�ɍ��킹�āA�r��L�΂�
	if(hypot(tx,ty)>=AXISLEN_A+AXISLEN_B){

		sPos[0] = (short) (atan2(ty,tx)/M_PI*1800.f);
		sPos[1] = 0;

	}
	else{

		//�]���藝�����Z
		a = acos( (-(tx*tx+ty*ty) + AXISLEN_A*AXISLEN_A + AXISLEN_B*AXISLEN_B) / (2 * AXISLEN_A * AXISLEN_B));
		b = s*acos( (- AXISLEN_A*AXISLEN_A + AXISLEN_B*AXISLEN_B + (tx*tx+ty*ty)) / (2 * AXISLEN_A * sqrt(tx*tx+ty*ty)));

		//�w���X/Y���W�̕����ɂ���āA�p�x�̌v�Z���@��I��
		if(tx<0){
			if(ty>=0) thete1 = M_PI + atan(ty/tx) +b;
			else thete1 = atan(ty/tx) + b - M_PI;
		}
		else thete1 = atan(ty/tx)+b;
		thete2 = -(M_PI-a)*s;


		//���܂����p�x��360�x�@�ɕϊ�
		if(thete1!=0.0) thete1 = thete1 / M_PI * 180.0;
		if(thete2!=0.0) thete2 = thete2 / M_PI * 180.0;

		//�ϊ������p�x��0.1�x�P�ʂɕϊ����A���[�^�̏o�͕����ɍ��킹�ĕ�����ύX�iID1�j
		sPos[0] = (short) (thete1*10.0);
		sPos[1] = (short) (thete2*10.0);


	}
	//�A�[����2���̉��͈͐���
	if(sPos[0]<-ARM_RAD_RANGE) sPos[0]=-ARM_RAD_RANGE;
	else if(sPos[0]>ARM_RAD_RANGE) sPos[0]=ARM_RAD_RANGE;

	if(sPos[1]<-ARM_RAD_RANGE) sPos[1]=-ARM_RAD_RANGE;
	else if(sPos[1]>ARM_RAD_RANGE) sPos[1]=ARM_RAD_RANGE;

	//Z���W�̕ϊ�
	sPos[2] = HEIGHT_TO_RAD(z);

	//�n���h��2���̕ϊ�
	if(num>3){
		//�O���b�v��
		sPos[4] = WIDTH_TO_RAD(w,CROW_POS);

		if(sPos[4]<-HAND_WIDTH_RANGE) sPos[4]=-HAND_WIDTH_RANGE;
		else if(sPos[4]>HAND_WIDTH_RANGE) sPos[4]=HAND_WIDTH_RANGE;

		sPos[3] = -sPos[0]-sPos[1];
		sPos[3] += (short) (yaw*10.0);
	}

}



/************************************************

	int RSTorqueOnOff( HID_UART_DEVICE dev, short sMode ,BYTE id,int num)
	
	�T�v�F���[�^�̃g���N��؂�ւ���֐��BID���A�����������̃��[�^�𓯎��ɐݒ�\�B

	�����F
		HID_UART_DEVICE dev	�c �ʐM�n���h��
		short sMode			�c �Q�C����ON/OFF���w��B0=off�A1=ON
		BYTE id				�c �؂�ւ����J�n���郂�[�^��ID�i�����̃��[�^��؂�ւ���ꍇ�A�擪�̃��[�^��ID�j
		int num				�c �؂�ւ����s�����[�^��

	�߂�l�F
		����ɏ��������s�ł�����TRUE�A�����łȂ����FALSE

*************************************************/
int RSTorqueOnOff( HID_UART_DEVICE dev, short sMode ,BYTE id,int num)
{
	unsigned char	sendbuf[256],*bufp;				//���M�o�b�t�@�֌W
	unsigned char	sum;							//�`�F�b�N�T���v�Z�p
	int				ret;							//�߂�l�L�^�p
	DWORD			data_len=0,len=0;				//�p�P�b�g���Ə������݃T�C�Y�擾�p
	unsigned char	i;


	//���M�o�b�t�@�N���A
	memset( sendbuf, 0x00, sizeof( sendbuf ));

	//�p�P�b�g�쐬
	//1�D�w�b�_�E���ʕ����̍쐬
	sendbuf[0]  = (unsigned char)0xFA;				// �w�b�_�[1
	sendbuf[1]  = (unsigned char)0xAF;				// �w�b�_�[2
	sendbuf[2]  = (unsigned char)0x00;				// �T�[�{ID(���0)
	sendbuf[3]  = (unsigned char)0x00;				// �t���O(���0)
	sendbuf[4]  = (unsigned char)0x24;				// �A�h���X(�g���NON/OFF 0x24=36)
	sendbuf[5]  = (unsigned char)0x01+1;			// ����(1byte)
	sendbuf[6]  = (unsigned char)num;				// ���[�^�̌�

	//���ʕ����̃p�P�b�g�����L�^
	data_len = 7;			

	//2�D�T�[�{�ʕ����̃p�P�b�g�쐬
	bufp = &sendbuf[7];								// ���M�o�b�t�@�̌ʃ��b�Z�[�W�����̊J�n�A�h���X����

	//���������郂�[�^�̌��������A�ʂ̃p�P�b�g��ǉ�
	for(i=0;i<num;i++){
		*bufp++ = id+i;								//���[�^��ID
		data_len++;									//�p�P�b�g����1byte���Z

		*bufp++ = (unsigned char)(sMode&0x00FF);	//ON�EOFF�t���O
		data_len++;									//�p�P�b�g����1byte���Z
	}

	//3�D�`�F�b�N�T���̌v�Z
	//�`�F�b�N�T���́A���M�o�b�t�@��3byte��(�T�[�{ID)�`�I�[��1byte����XOR�����l�ł��B
	sum = sendbuf[2];
	for( i = 3; i < data_len; i++ ){
		sum = (unsigned char)(sum ^ sendbuf[i]);
	}
	sendbuf[data_len] = sum;						// ���܂����`�F�b�N�T���𑗐M�o�b�t�@�̍Ō�ɑ��
	data_len++;										//�p�P�b�g����1byte���Z

	//4�D���b�Z�[�W�̑��M
	ret = HidUart_Write( dev, (BYTE*) sendbuf, data_len, &len );

	if(ret!=HID_UART_SUCCESS) return FALSE;

	//5�D���[�J���G�R�[�̓ǂݎ��
	return ReadLocalEcho(dev,sendbuf,data_len);
}



/************************************************

	int RSGetAngle( HID_UART_DEVICE dev ,BYTE id,short *getParam)
	
	�T�v�F���[�^�̌��݈ʒu���擾����B���݈ʒu�̎擾�͓�����1�̃��[�^�����Ή����Ă��Ȃ�

	�����F
		HID_UART_DEVICE dev	�c �ʐM�n���h��
		BYTE id				�c ���݈ʒu���擾���郂�[�^��ID
		short *getParam		�c �擾�������݈ʒu���i�[����ϐ��ւ̃|�C���^

	�߂�l�F
		����ɏ��������s�ł�����TRUE�A�����łȂ����FALSE

*************************************************/
int RSGetAngle( HID_UART_DEVICE dev ,BYTE id,short *getParam)
{
	unsigned char	sendbuf[32];
	unsigned char	readbuf[128];
	unsigned char	sum;
	DWORD			i;
	int				ret;
	unsigned long	len, readlen;
	short			angle;

	// �o�b�t�@�N���A
	memset( sendbuf, 0x00, sizeof( sendbuf ));

	// �p�P�b�g�쐬
	sendbuf[0]  = (unsigned char)0xFA;				// �w�b�_�[1
	sendbuf[1]  = (unsigned char)0xAF;				// �w�b�_�[2
	sendbuf[2]  = (unsigned char)id;				// �T�[�{ID
	sendbuf[3]  = (unsigned char)0x0f;				// �t���O(0x0f=�w��A�h���X����w��o�C�g�擾)
	sendbuf[4]  = (unsigned char)0x2a;				// �擾���f�[�^�̃A�h���X(���݈ʒu=0x2a)
	sendbuf[5]  = (unsigned char)0x02;				// �擾����f�[�^�̒���(���݈ʒu=2byte)
	sendbuf[6]  = (unsigned char)0x00;				// ��(0)

	
	// �`�F�b�N�T���̌v�Z
	sum = sendbuf[2];
	for( i = 3; i < 7; i++ ){
		sum = (unsigned char)(sum ^ sendbuf[i]);
	}
	sendbuf[7] = sum;								// �`�F�b�N�T��

	// �p�P�b�g�𑗐M
	ret = HidUart_Write(dev,sendbuf, 8, &len);

	//���[�J���G�R�[��ǂݎ��
	if(!ReadLocalEcho(dev,sendbuf,len)) return FALSE;

	// �������M�ł����p�P�b�g�����f�[�^�T�C�Y�����������ꍇ�A�G���[
	if( len < 8 ) return FALSE;


	// ��M�o�b�t�@�̓ǂݍ���
	memset( readbuf, 0x00, sizeof( readbuf ));

	//��M�o�b�t�@�̃p�P�b�g���̌v�Z
	//	Header(2byte) + ID(1byte) + Flags(1byte) + Address(1byte) + Length(1byte) + Count(1byte) + Dada(2byte) + Sum(1byte)
	readlen = (2) + (1) + (1) + (1) + (1) + (1) + (2) + (1);
	len = 0;

	//�o�b�t�@�̎�M
	HidUart_Read(dev,readbuf, readlen, &len);

	//��M�o�b�t�@�̃p�P�b�g�����A�v�Z�ŋ��߂�����(readlen)�ƈقȂ�ꍇ�A�G���[
	if( len < readlen)  return FALSE;

	// ��M�f�[�^�̃`�F�b�N�T���m�F
	sum = readbuf[2];
	for( i = 3; i < readlen; i++ ){
		sum = sum ^ readbuf[i];
	}

	//�`�F�b�N�T�����قȂ�ꍇ�A�G���[
	if( sum ) return FALSE;

	//��M�o�b�t�@����A�ǂݎ�������݈ʒu�̃f�[�^�����o��
	angle = ((readbuf[8] << 8) & 0x0000FF00) | (readbuf[7] & 0x000000FF);
	if(getParam) *getParam = angle;

	return TRUE;
}


/************************************************

	int RSMove( HID_UART_DEVICE dev , short *sPoss, unsigned short sTime ,BYTE id,int num)
	
	�T�v�F���[�^���w��̊p�x�ɓ������BID���A�����������̃��[�^����x�ɓ��������Ƃ��\�B

	�����F
		HID_UART_DEVICE dev	�c �ʐM�n���h��
		short *sPoss		�c �ڕW�ʒu���L�^�����z��ϐ��ւ̃|�C���^�B�J�nID�̖ڕW�l�́A�o�b�t�@�̐擪���珇�Ɏg�p�����
		unsigned short sTime �c �ڕW�ʒu�܂ł̑J�ڎ���(10�~���b�P��)
		BYTE id				�c ���������[�^��ID�i�����̃��[�^�𓮂����ꍇ�A�擪�̃��[�^��ID�j
		int num				�c ���������[�^��

	�߂�l�F
		����ɏ��������s�ł�����TRUE�A�����łȂ����FALSE

*************************************************/
int RSMove( HID_UART_DEVICE dev , short *sPoss, unsigned short sTime ,BYTE id,int num)
{
	unsigned char	sendbuf[256],*bufp;
	unsigned char	sum;
	unsigned char	i;
	int				ret;
	unsigned long	len,data_len;


	// �o�b�t�@�N���A
	memset( sendbuf, 0x00, sizeof( sendbuf ));

	// �p�P�b�g�쐬
	sendbuf[0]  = (unsigned char)0xFA;				    // �w�b�_�[1
	sendbuf[1]  = (unsigned char)0xAF;				    // �w�b�_�[2
	sendbuf[2]  = (unsigned char)0;						// ID(0)
	sendbuf[3]  = (unsigned char)0x00;				    // �t���O(0x00)
	sendbuf[4]  = (unsigned char)0x1E;				    // �A�h���X(0x1E=30)
	sendbuf[5]  = (unsigned char)0x04+1;			    // ����(4byte)
	sendbuf[6]  = (unsigned char)num;				    // ���[�^�̌�

	//���ʕ����̃p�P�b�g�����L�^
	data_len = 7;

	//�ʂ̃f�[�^�쐬
	bufp = &sendbuf[7];
	for(i=0;i<num;i++){
		*bufp++ = id+i;								//���[�^ID
		data_len++;									//�p�P�b�g����1byte���Z

		//�ڕW�ʒu���o�b�t�@�ɏ�������(2byte)
		*bufp++ = (unsigned char)(sPoss[i]&0x00FF);
		*bufp++ = (unsigned char)((sPoss[i]&0xFF00)>>8);
		data_len+=2;								//�p�P�b�g����2byte���Z

		//�J�ڎ��Ԃ��o�b�t�@�ɏ�������(2byte)
		*bufp++ = (unsigned char)(sTime&0x00FF);
		*bufp++ = (unsigned char)((sTime&0xFF00)>>8);
		data_len+=2;								//�p�P�b�g����2byte���Z
	}


	// �`�F�b�N�T���̌v�Z
	sum = sendbuf[2];
	for( i = 3; i < data_len; i++ ){
		sum = (unsigned char)(sum ^ sendbuf[i]);
	}
	sendbuf[data_len] = sum;						// ���M�o�b�t�@�Ƀ`�F�b�N�T����ǉ�
	data_len++;										//�p�P�b�g����1byte���Z

	// �p�P�b�g�𑗐M
	ret = HidUart_Write( dev, (BYTE*) sendbuf, data_len, &len );
	if(ret!=HID_UART_SUCCESS) return FALSE;

	//���[�J���G�R�[�̓ǂݎ��
	return ReadLocalEcho(dev,sendbuf,data_len);

}


/************************************************

	int ReadLocalEcho(HID_UART_DEVICE dev ,unsigned char *sendbuf,DWORD data_len)
	
	�T�v�F
		���M���b�Z�[�W�̃��[�J���G�R�[��ǂݏo���֐��B
		���� data_len �̒����������b�Z�[�W����M���A ���� *sendbuf �̓��e�Ɠ��ꂩ��r���s��

	�����F
		HID_UART_DEVICE dev		�c �ʐM�n���h��
		unsigned char *sendbuf	�c ���M���b�Z�[�W���e�ւ̃|�C���^
		DWORD data_len			�c ���M���b�Z�[�W�̃T�C�Y

	�߂�l�F
		���M���b�Z�[�W�Ɠ���̓��e����M�ł�����TRUE�A�����łȂ����FALSE

*************************************************/
int ReadLocalEcho(HID_UART_DEVICE dev ,unsigned char *sendbuf,DWORD data_len)
{

	unsigned char readbuf[1024];
	DWORD len=0;
	memset(readbuf,0,sizeof(readbuf));

	//data_len �̃T�C�Y�������b�Z�[�W����M
	HidUart_Read( dev, (BYTE*) readbuf, data_len, &len );

	//��M���b�Z�[�W�̃T�C�Y���قȂ�ꍇ�A�G���[
	if(data_len!=len) return FALSE;

	//��M���b�Z�[�W�Ƒ��M���b�Z�[�W���r
	for(DWORD i=0;i<len;i++){

		//��M���b�Z�[�W�Ƒ��M���b�Z�[�W���قȂ�ꍇ�A�G���[
		if(readbuf[i]!=sendbuf[i]) return FALSE;
	}
	return TRUE;
}




/************************************************

	int int RSWriteMem( HID_UART_DEVICE dev , BYTE address , BYTE size , BYTE id , BYTE *data , int num)
	
	�T�v�F
		���[�^�̃p�����[�^������������B�A�����������̃��[�^�E�����̃A�h���X�ɏ������݂��\
		�A�h���X�E�T�C�Y�E���[�^���E���f�[�^���w�肷��

	�����F
		HID_UART_DEVICE dev	�c �ʐM�n���h��
		BYTE address		�c �f�[�^���������ރA�h���X�i�A�h���X�̏ڍׂ�RS304MD�̎������Q�Ɓj
		BYTE size			�c ���[�^1������ɏ������ރf�[�^�̃T�C�Y(byte�P��)
		BYTE id				�c ���������[�^��ID�i�����̃��[�^�𓮂����ꍇ�A�擪�̃��[�^��ID�j
		BYTE *data			�c �������݃f�[�^���e�̔z��ϐ��ւ̃|�C���^
		int num				�c ���������[�^��

	�߂�l�F
		����ɏ��������s�ł�����TRUE�A�����łȂ����FALSE

*************************************************/
int RSWriteMem( HID_UART_DEVICE dev , BYTE address , BYTE size , BYTE id , BYTE *data , int num)
{
	unsigned char	sendbuf[256],*bufp;
	unsigned char	sum;
	unsigned char	i,j;
	int				ret;
	unsigned long	len,data_len;


	// �o�b�t�@�N���A
	memset( sendbuf, 0x00, sizeof( sendbuf ));

	// �p�P�b�g�쐬
	sendbuf[0]  = (unsigned char)0xFA;				    // �w�b�_�[1
	sendbuf[1]  = (unsigned char)0xAF;				    // �w�b�_�[2
	sendbuf[2]  = (unsigned char)0;						// ID(0)
	sendbuf[3]  = (unsigned char)0x00;				    // �t���O(0x00)
	sendbuf[4]  = (unsigned char)address;				    // �A�h���X(0x1E=30)
	sendbuf[5]  = (unsigned char)size+1;			    // ����(4byte)
	sendbuf[6]  = (unsigned char)num;				    // ���[�^�̌�

	//���ʕ����̃p�P�b�g�����L�^
	data_len = 7;

	//�ʂ̃f�[�^�쐬
	bufp = &sendbuf[7];
	for(i=0;i<num;i++){
		*bufp++ = id+i;								//���[�^ID
		data_len++;									//�p�P�b�g����1byte���Z

		for(j=0;j<size;j++){
			*bufp++ = (unsigned char)data[j];		//�f�[�^����1byte���p�P�b�g�ɒǉ�
			data_len++;								//�p�P�b�g����2byte���Z
		}
	}


	// �`�F�b�N�T���̌v�Z
	sum = sendbuf[2];
	for( i = 3; i < data_len; i++ ){
		sum = (unsigned char)(sum ^ sendbuf[i]);
	}
	sendbuf[data_len] = sum;						// ���M�o�b�t�@�Ƀ`�F�b�N�T����ǉ�
	data_len++;										//�p�P�b�g����1byte���Z

	// �p�P�b�g�𑗐M
	ret = HidUart_Write( dev, (BYTE*) sendbuf, data_len, &len );
	if(ret!=HID_UART_SUCCESS) return FALSE;

	//���[�J���G�R�[�̓ǂݎ��
	return ReadLocalEcho(dev,sendbuf,data_len);

}

/************************************************

	int SetTXOpenDrain(HID_UART_DEVICE dev )
	
	�T�v�F
		USB-to-UART�iCP2110�j�̃|�[�g�ݒ�ɂ��āATX��Open-Drain�ɐݒ�ύX����B
		���{�b�g�{�̂ƒʐM����ۂɂ́A�K�����̐ݒ肪�K�v�i�ݒ��ύX����ƃ��{�b�g�{�̂ɋL�^�����j�B

	�����F
		HID_UART_DEVICE dev	�c �ʐM�n���h��

	�߂�l�F
		HID_UART_STATUS �ɂĒ�`����Ă���e���l�BHID_UART_SUCCESS�ł���ΐ����A����ȊO�͎��s

*************************************************/
int SetTXOpenDrain(HID_UART_DEVICE dev )
{
	//GPIO�̐ݒ�ŁATX �� Open-Drain �ɐݒ肷��K�v������
	BYTE pinConfig[13];
	BOOL useSuspendValues;
	WORD suspendValue;
	WORD suspendMode;
	BYTE rs485Level;
	BYTE clkDiv;

	//���݂� Pin Config ���擾
	HidUart_GetPinConfig(dev,  pinConfig,  &useSuspendValues, &suspendValue, &suspendMode, &rs485Level, &clkDiv);

	//TX �� TX-Open-Drain(0x01) �ɕύX
	pinConfig[10] = 0x01;

	//Pin Config ���X�V
	return HidUart_SetPinConfig(dev,  pinConfig, useSuspendValues, suspendValue, suspendMode,rs485Level, clkDiv);

}
