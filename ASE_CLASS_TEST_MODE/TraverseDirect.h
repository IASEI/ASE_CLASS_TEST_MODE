#ifndef __TRAVERSEDIRECT_H__
#define __TRAVERSEDIRECT_H__
/*
*遍历文件夹类
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
		
		virtual unsigned long long Traverse();		//遍历文件夹接口
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
		virtual bool TraverseChild(std::string dir,unsigned long long dirNum);	//遍历子文件夹
	protected:
		std::string mPath;				//绝对路径
		std::string mType;				//文件类型
		std::vector<std::string> mDirectPath;//文件夹路径
		std::vector<std::string> mFilePath;//文件路径
		unsigned long long mDirectNum;	//文价夹数量
		unsigned long long mFileNum;	//文件数量
		unsigned long long mDepth;		//深度
		unsigned long long mTraverseDepth;//深度
		bool isFirstDepth;				//是否只遍历第一层
		bool isError;					//是否含有错误
	};
}

#endif // !__TRAVERSEDIRECT_H__



