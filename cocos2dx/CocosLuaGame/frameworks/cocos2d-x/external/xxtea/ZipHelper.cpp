#include "ZipHelper.h"

#include "cocos2d.h"
#include "unzip.h"

USING_NS_CC;

static const std::string emptyFilename("");

static int getCurrentFileInfo(unzFile zipFile, std::string *filename, unz_file_info *info)
{
	char path[FILENAME_MAX + 1];
	int ret = unzGetCurrentFileInfo(zipFile, info, path, sizeof(path), NULL, 0, NULL, 0);
	if (ret != UNZ_OK)
	{
		*filename = emptyFilename;
	}
	else
	{
		filename->assign(path);
	}
	return ret;
}

struct ZipHelper::IMP_T
{
	unzFile zipFile;
};

ZipHelper *ZipHelper::create(const char *zipFilename)
{
	ZipHelper *zip = new ZipHelper();
	if (zip->initWithFilename(zipFilename))
	{
		zip->autorelease();
		return zip;
	}
	else
	{
		delete zip;
		return NULL;
	}
}

ZipHelper *ZipHelper::createWithBuffer(const void* buffer, unsigned long size)
{
	ZipHelper *zip = new ZipHelper();
	if (zip->initWithBuffer(buffer, size))
	{
		zip->autorelease();
		return zip;
	}
	else
	{
		delete zip;
		return NULL;
	}
}

ZipHelper::ZipHelper()
{
	m = new ZipHelper::IMP_T;
	m->zipFile = nullptr;
}

ZipHelper::~ZipHelper(void)
{
	close();
	delete m;
	m = nullptr;
}

const std::string ZipHelper::getFirstFilename(void)
{
	if (unzGoToFirstFile(m->zipFile) != UNZ_OK) return emptyFilename;
	std::string path;
	unz_file_info info;
	getCurrentFileInfo(m->zipFile, &path, &info);
	return path;
}

const std::string ZipHelper::getNextFilename(void)
{
	if (unzGoToNextFile(m->zipFile) != UNZ_OK) return emptyFilename;
	std::string path;
	unz_file_info info;
	getCurrentFileInfo(m->zipFile, &path, &info);
	return path;
}

unsigned char* ZipHelper::getFileData(const char *filename, unsigned long *filesize)
{
	unsigned char *buffer = nullptr;
	*filesize = 0;

	do 
	{
		int ret = unzLocateFile(m->zipFile, filename, 1);
		CC_BREAK_IF(UNZ_OK != ret);

		std::string path;
		unz_file_info info;
		CC_BREAK_IF(UNZ_OK != getCurrentFileInfo(m->zipFile, &path, &info));

		ret = unzOpenCurrentFile(m->zipFile);
		CC_BREAK_IF(UNZ_OK != ret);

		buffer = new unsigned char[info.uncompressed_size];
		int size = 0;
		size = unzReadCurrentFile(m->zipFile, buffer, info.uncompressed_size);
		CCAssert(size == 0 || size == (int)info.uncompressed_size, "the file size is wrong");

		*filesize = info.uncompressed_size;
		unzCloseCurrentFile(m->zipFile);
	} while (0);

	return buffer;
}

void ZipHelper::close(void)
{
	if (m->zipFile)
	{
		unzClose(m->zipFile);
		m->zipFile = nullptr;
	}
}

bool ZipHelper::initWithFilename(const char *zipFilename)
{
	if (!zipFilename || strlen(zipFilename) == 0) return false;

	m->zipFile = unzOpen(zipFilename);
	if (!m->zipFile) return false;

	return true;
}

bool ZipHelper::initWithBuffer(const void *buffer, uLong size)
{
	if (!buffer || size == 0) return false;

	m->zipFile = unzOpenBuffer(buffer, size);
	if (!m->zipFile) return false;

	return true;
}

