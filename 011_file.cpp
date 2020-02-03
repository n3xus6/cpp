/*
 * 011_file.cpp
 * 
 * Dummy format to show reading binary data.
 * 
 * ====== ========== ================
 * size   name       description
 * =====  ========== =================
 * 1      cmt length length of comment
 * var    cmt        comment
 * 2      count      number of strings
 * 1      str length string length n
 * var    string     string n (string ends with '\0')
 * ...
 * 3      marker     'E','N','D'
 * 
 * Test:
 * > './011_file /test/test.bin'
 *  Open file: test.bin
 *  String: The
 *  String: Quick
 *  String: Brown
 *  String: Fox
 */
#include<iostream>
#include<fstream>
#include<cstdint>
#include<string>
using namespace std;

struct filehandle
{
	ifstream ifs;
	filehandle(const char *filepath) { ifs.open(filepath); }
	~filehandle() { ifs.close(); }
};

static char buf[512];

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr << "Usage: " << argv[0] << " <file.bin>\n";
		return 1;
	}

	char *filename = argv[1];

	filehandle filehnd(filename);
	if (filehnd.ifs.fail())
		return 1;

	cout << "Open file: " << filename << '\n';

	streambuf *rdbuf = filehnd.ifs.rdbuf();

	long long int filelen = rdbuf->pubseekoff(0, ios_base::end);
	if (filelen < 6) // custom-format file with no comment, no strings has 6 bytes
		return 0;

	rdbuf->pubseekpos(0);
	if (rdbuf->sgetn(buf, 1) != 1) // read comment length
		return 1;
	
	rdbuf->pubseekoff(buf[0], ios_base::cur); // skip comment

	if (rdbuf->sgetn(buf, 2) != 2) // read string number
		return 1;

	uint16_t cnt = ((unsigned char) buf[1] << 8 | (unsigned char) buf[0]);

	while (cnt--)
	{
		if (rdbuf->sgetn(buf, 1) != 1) // read string length
			return 1;

		int length = buf[0];

		if (rdbuf->sgetn(buf, length) != length) // read string
			return 1;

		buf[length] = '\0';
		cout << "String: " << buf << '\n';
	}

	if (rdbuf->sgetn(buf, 3) != 3) // check last bytes in file
		return 1;

	if (buf[0] != 'E' || buf[1] != 'N' || buf[2] != 'D')
		return 1;

	return 0;
}
