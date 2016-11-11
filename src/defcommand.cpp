#include "defcommand.h"

//CaoProvider�̐ݒ�
char* ControllerName;
char* CaoProvName;
char* ConnectionParam;
char* Manufactur;
char* RobotName;
int AxisNum;
char* AxialType[10];
bool IsGripper;

//CommonCommand�̐ݒ�
//�������̊֐��ɂ�"NOT_IMPLEMENTED"��������
//C1.�A���[���N���A
char* C1_Command;
//C2.�A���[�����̎擾
char* C2_Command;
//C3.�֐ߍ��W�n�̈ʒu�t�B�[�h�o�b�N���̎擾
char* C3_Command;
//C4.�}�j�s�����[�^���̎擾
char* C4_Command;
//C5.�֐ߍ��W�n�̃\�t�g���~�b�g�l���擾
char* C5_Command;
//C6.���j�b�g�̏�Ԏ擾
char* C6_Command;
//C7.�S���T�[�{OFF
char* C7_Command;
char* C7_Option;
//wchar_t* C7_Option;
//C8.�S���T�[�{ON
char* C8_Command;
char* C8_Option;
//wchar_t* C8_Option;
//C9.�֐ߍ��W�n�̃\�t�g���~�b�g�l�ݒ�
char* C9_Command;

//MiddleLevelMotionCommand�̐ݒ�
//M1.�O���b�p�����
char* M1_Command;
//M2.�}�j�s�����[�^�̐ݒ�ʒu���擾
char* M2_Command;
//M3.�������W�n�̈ʒu�t�B�[�h�o�b�N���̎擾
char* M3_Command;
//M4.���𓮍쎞�̍ő哮�쑬�x���擾
char* M4_Command;
//M5.�֐ߓ��쎞�̍ő哮�쑬�x���擾
char* M5_Command;
//M6.���𓮍쎞�̍ŏ�����������x���擾
char* M6_Command;
//M7.�֐ߓ��쎞�̍ŏ�����������x���擾
char* M7_Command;
//M8.�������W�n�̃\�t�g���~�b�g�l���擾
char* M8_Command;
//M9.�O���b�p�̊J����
char* M9_Command;
//M10.�������W�n�̒������(��Ύw��)
char* M10_Command;
//M11.�������W�n�̒������(���Ύw��)
char* M11_Command;
//M12.�֐ߍ��W�n�̒������(�����E��Ύw��)
char* M12_Command;
//M13.�֐ߍ��W�n�̒������(�����E���Ύw��)
char* M13_Command;
//M14.�֐ߍ��W�n�̒������(�֐߁E��Ύw��)
char* M14_Command;
//M15.�֐ߍ��W�n�̒������(�֐߁E���Ύw��)
char* M15_Command;
//M16.�O���b�p���J��
char* M16_Command;
//M17.����̈ꎞ��~
char* M17_Command;
//M18.����̍ĊJ
char* M18_Command;
//M19.����̒�~
char* M19_Command;
//M20.���𓮍쎞�̉������Ԃ�ݒ�
char* M20_Command;
//M21.�֐ߓ��쎞�̉������Ԃ�ݒ�
char* M21_Command;
//M22.�}�j�s�����[�^�̐ݒu�ʒu��ݒ�
char* M22_Command;
//M23.����_�̃t�����W�ʂ���̃I�t�Z�b�g�ʂ�ݒ�
char* M23_Command;
//M24.���𓮍쎞�̍ő哮�쑬�x��ݒ�
char* M24_Command;
//M25.�֐ߓ��쎞�̍ő哮�쑬�x��ݒ�
char* M25_Command;
//M26.���𓮍쎞�̍ŏ�����������Ԃ�ݒ�
char* M26_Command;
//M27.�֐ߓ��쎞�̍ŏ�����������Ԃ�ݒ�
char* M27_Command;
//M28.�������W�n�̃\�t�g���~�b�g�l��ݒ�
char* M28_Command;
//M29.���𓮍쎞�̑��x��ݒ�
char* M29_Command;
//M30.�֐ߓ��쎞�̑��x��ݒ�
char* M30_Command;
//M31.�������W�n�̉~�ʕ��(��Ύw��)
char* M31_Command;
//M32.�������W�n�̉~�ʕ��(���Ύw��)
char* M32_Command;
//M33.���_���A���̈ʒu�E�p����ݒ�
char* M33_Command;
//M34.���_���A���̈ʒu�E�p�����擾
char* M34_Command;
//M35.���_���A����
char* M35_Command;