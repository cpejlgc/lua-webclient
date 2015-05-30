﻿/****************************************************************************
Copyright (c) 2014      dpull.com

http://www.dpull.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#pragma once

struct CWebRequest;
typedef size_t CWebClientWriteCallback(char* pszBuffer, size_t uBlockSize, size_t uCount, void* pvArg);

class CWebClient
{
public:
	CWebClient();
	virtual ~CWebClient();

public:
	bool Setup(CWebClientWriteCallback* pCallback, void* pvUserData);
	void Clear();

    bool Query(void** pHandle, char** ppszError);
	void* Request(const char szUrl[], const char* pPostData, size_t uPostDataLen);
    void RemoveRequest(void* pHandle);
    
	const void* GetUserData() { return m_pvUserData; }

private:
    bool RealQuery(void** pHandle, char** ppszError);
    
private:
    typedef std::map<CURL*, CWebRequest*> CWebRequestTable;
    
	CWebRequestTable			m_WebRequestTable;
	CURLM*						m_pCurlMHandle;
	CWebClientWriteCallback*	m_pCallback;
	void*						m_pvUserData;
};
