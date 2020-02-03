#include "TraverseDirect.h"

namespace ASE
{

	TraverseDirect::TraverseDirect():mDirectNum(0), mFileNum(0), mDepth(0), isFirstDepth(true), isError(false), mType("*.*"), mTraverseDepth(0)
	{
	}

	TraverseDirect::TraverseDirect(const std::string path, std::string type) :mPath(path),mDirectNum(0), mFileNum(0), mDepth(0), isFirstDepth(false), isError(false), mType(type), mTraverseDepth(0)
	{
		this->mPath += '/';
		if (_chdir(this->mPath.c_str()))
		{
			this->isError = true;
			std::cout << "�ļ��в�����" << std::endl;
		}
	}

	unsigned long long TraverseDirect::Traverse()
	{
		unsigned long long dirNum = 0;
		if (this->isError)
		{
			std::cout << "���д���" << std::endl;
			return 0;
		}
		TraverseChild(this->mPath, dirNum);
		this->mDirectNum = this->mDirectPath.size();
		this->mFileNum = this->mFilePath.size();
		return this->mDirectNum + this->mFileNum;
	}

	unsigned long long TraverseDirect::TraverseAll()
	{
		DWORD dwSize = MAX_PATH;
		unsigned long long dirNum = 0;
		char szLogicalDrives[MAX_PATH] = { 0 };
		//��ȡ�߼����������ַ���
		DWORD dwResult = GetLogicalDriveStrings(dwSize, (LPWSTR)szLogicalDrives);
		//�����ȡ���Ľ��
		if (dwResult > 0 && dwResult <= MAX_PATH) {
			char* szSingleDrive = szLogicalDrives;  //�ӻ�������ʼ��ַ��ʼ
			while (*szSingleDrive) {
				printf("Drive: %s\n", szSingleDrive);   //�����������������������
				if (GetDriveType((LPWSTR)szSingleDrive) != DRIVE_REMOVABLE && GetDriveType((LPWSTR)szSingleDrive) != DRIVE_FIXED )
					continue;
				std::string path = szSingleDrive;
				path[path.size() - 1] = '/';
				TraverseChild(path, dirNum);
				szSingleDrive += strlen(szSingleDrive) + 1;// ��ȡ��һ������������ʼ��ַ
			}
		}
		this->mDirectNum = this->mDirectPath.size();
		this->mFileNum = this->mFilePath.size();
		return this->mDirectNum + this->mFileNum;
	}

	std::string TraverseDirect::GetPath() const
	{
		return this->mPath;
	}

	unsigned long long TraverseDirect::GetDirectNum() const
	{
		return this->mDirectNum;
	}

	unsigned long long TraverseDirect::GetFileNum() const
	{
		return this->mFileNum;
	}

	unsigned long long TraverseDirect::GetDepth() const
	{
		return this->mDepth;
	}

	bool TraverseDirect::IsFirstDepth() const
	{
		return this->isFirstDepth;
	}

	void TraverseDirect::Clear()
	{
		this->mDepth = 0;
		this->mDirectNum = 0;
		this->mDirectPath.swap(std::vector<std::string>());
		this->mFileNum = 0;
		this->mFilePath.swap(std::vector<std::string>());
		this->mPath = "";
		this->mTraverseDepth = 0;
		this->mType = "*.*";
		this->isError = false;
		this->isFirstDepth = false;
	}

	//protected
	void TraverseDirect::InitAboslutePath()
	{
		/*
		char path[255] = { '\0' };
		getcwd(path, 255 * sizeof(char));
		this->mPath = path;
		char pathLast = this->mPath[this->mPath.size() - 1];
		if (!(pathLast == '\\' || pathLast == '/'))
			this->mPath += '/';
		*/
	}

	bool TraverseDirect::TraverseChild(std::string dir, unsigned long long dirNum)
	{
		dirNum++;
		//���Ȳ���dir�з���Ҫ����ļ� 
		long hFile;
		_finddata_t fileinfo;
		if ((hFile = _findfirst((dir+this->mType).c_str(), &fileinfo)) != -1)
		{
			do
			{
				//����ǲ���Ŀ¼ 
				//�������,����д��� 
				if (!(fileinfo.attrib & _A_SUBDIR))
				{
					this->mFilePath.push_back(dir + fileinfo.name);
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);

		}
		if (this->isFirstDepth)
		{
			this->mDepth = 1;
			return true;
		}
		else
		{
			this->mDepth = dirNum;
			if (this->mTraverseDepth != 0&& this->mDepth >= this->mTraverseDepth)
					return true;
		}
		
		if ((hFile = _findfirst((dir + "*.*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				if ((fileinfo.attrib & _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					{
						std::string subdir=dir+ fileinfo.name+'/';
						this->mDirectPath.push_back(subdir);
						if (!this->TraverseChild(subdir, dirNum))
							return false;
					}
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
		return true;
	}

	TraverseDirect::~TraverseDirect()
	{
	}

}
