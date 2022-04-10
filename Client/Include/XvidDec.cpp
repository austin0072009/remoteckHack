#include "XvidDec.h"
#include <Windows.h>

#ifdef _DEBUG
#pragma comment(lib, "libxvidcored.lib")
#else
#pragma comment(lib, "libxvidcore.lib")
#endif // _DEBUG

CXvidDec::CXvidDec(int version, unsigned int cpu_flags, int debug)
{
	m_version = version;
	m_bOpened = false;
	/* XviD core initialization */
	m_xvid_gbl_init.version = version;
	m_xvid_gbl_init.cpu_flags = cpu_flags;
	m_xvid_gbl_init.debug = debug;
	if (xvid_global(NULL, XVID_GBL_INIT, &m_xvid_gbl_init, NULL) < 0)
		m_bInited = false;
	else
		m_bInited = true;
}

CXvidDec::~CXvidDec()
{
	
}
void CXvidDec::AttachCaller(int width, int height) 
{
	m_width = width ;
	m_height = height ; 
	if((m_width > 0) && (m_height > 0)) 
	{
		m_image = new unsigned char [m_width * m_height * 3] ; 
		memset(m_image, 0, m_width * m_height * 3) ; 
	}
}
void CXvidDec::XVID_GLOBAL_INIT() {
/*------------------------------------------------------------------------
* XviD core initialization
	*----------------------------------------------------------------------*/
	xvid_gbl_init_t xvid_gbl_init;
	memset(&xvid_gbl_init, 0, sizeof(xvid_gbl_init));
	xvid_gbl_init.version = XVID_VERSION;
	xvid_gbl_init.cpu_flags = 0;//XVID_CPU_FORCE | XVID_CPU_ASM | XVID_CPU_SSE ; // force to use asm optimized routine
	/* Initialize XviD core -- Should be done once per __process__ */
	xvid_global(NULL, XVID_GBL_INIT, &xvid_gbl_init, NULL);
}
bool CXvidDec::Open(int width, int height, int cbit)
{
	if (!m_bInited) return false;
	if (m_bOpened) return false;
	
	int csp;
	switch (cbit)
	{
	case 16:
		csp = XVID_CSP_RGB555 | XVID_CSP_VFLIP;
		break;
	case 24:
		csp = XVID_CSP_BGR | XVID_CSP_VFLIP;
		break;
	case 32:
		csp = XVID_CSP_BGRA | XVID_CSP_VFLIP;
		break;
	default:
		return false;
	}
	
	/* XviD decoder initialization */
	memset(&m_xvid_dec_create, 0, sizeof(m_xvid_dec_create));
	m_xvid_dec_create.version = m_version;
	m_xvid_dec_create.width = width;
	m_xvid_dec_create.height = height;
	if (xvid_decore(NULL, XVID_DEC_CREATE, &m_xvid_dec_create, NULL) < 0)
		return false;
	
	/* XviD frame initialization */
	memset(&m_xvid_dec_frame, 0, sizeof(m_xvid_dec_frame));
	m_xvid_dec_frame.version = m_version;
	m_xvid_dec_frame.output.csp = csp;
	m_xvid_dec_frame.output.stride[0] = (m_xvid_dec_create.width * cbit / 8 + 3) / 4 * 4;
	
	m_bOpened = true;
	return true;
}

int CXvidDec::Decode(void *input, int inlen, void *output)
{
	if (!m_bOpened) return -1;
	
	m_xvid_dec_frame.bitstream = input;
	m_xvid_dec_frame.length = inlen;
	m_xvid_dec_frame.output.plane[0] = output;
	
	return xvid_decore(m_xvid_dec_create.handle, XVID_DEC_DECODE, &m_xvid_dec_frame, NULL);
}

bool CXvidDec::Close()
{
	if (m_bOpened && xvid_decore(m_xvid_dec_create.handle, XVID_DEC_DESTROY, NULL, NULL) >= 0)
	{
		m_bOpened = false;
		return true;
	}
	else return false;
}
