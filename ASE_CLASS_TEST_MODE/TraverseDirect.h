#ifndef __TRAVERSEDIRECT_H__
#define __TRAVERSEDIRECT_H__
/*
*�����ļ�����
*
*/
#include<iostream>
#include<vector>
#include<direct.h>
#include<io.h>
#include<Windows.h>

namespace ASE
{
	class TraverseDirect
	{
	public:
		TraverseDirect();
		TraverseDirect(const std::string path, std::string type="*.*");
		
		virtual unsigned long long Traverse();		//�����ļ��нӿ�
		unsigned long long TraverseAll();
		std::string GetPath()				const;
		unsigned long long GetDirectNum()	const;
		unsigned long long GetFileNum()		const;
		unsigned long long GetDepth()		const;
		bool IsFirstDepth()					const;
		virtual void Clear();

		~TraverseDirect();
	protected:
		inline void InitAboslutePath();
		virtual bool TraverseChild(std::string dir,unsigned long long dirNum);	//�������ļ���
	protected:
		std::string mPath;				//����·��
		std::string mType;				//�ļ�����
		std::vector<std::string> mDirectPath;//�ļ���·��
		std::vector<std::string> mFilePath;//�ļ�·��
		unsigned long long mDirectNum;	//�ļۼ�����
		unsigned long long mFileNum;	//�ļ�����
		unsigned long long mDepth;		//���
		unsigned long long mTraverseDepth;//���
		bool isFirstDepth;				//�Ƿ�ֻ������һ��
		bool isError;					//�Ƿ��д���
	};
}

#endif // !__TRAVERSEDIRECT_H__



