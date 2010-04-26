/*
 * This file is a part of Moorie
 *
 * Copyright (C) 2007-2010 Moorie Team - http://moorie.pl/
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "mailbox.h"

#include "stringutils.h"

CMailBox::CMailBox(const std::string &name, const std::string &usr, const std::string &passwd)
	: user(usr)
        , mailbox(name)
	, password(passwd)
	, bufferPos(0)
	, buffer(NULL)
	, usecnt(0)
	, failcnt(0)
	, successcnt(0)
	, prefweight(0)
	, scoreNeedsUpdate(true)
	, validAccount(true)
        , bytesSend( 0 )
        , bytesRead ( 0 )
        , uploadSpeed( 0 )
        , downloadSpeed( 0 )
{

	segDownload = false;
}

CMailBox::~CMailBox() {
}

void CMailBox::setFileName(std::string file) {
	filename = file;
}

void CMailBox::setFileCRC(int crc) {

}
void CMailBox::setCookie( std::string cookie ) const
{
}

std::string& CMailBox::doGet(std::string url, bool  header)
{

	return this->result;
}

std::string& CMailBox::doPost(std::string url, std::string vars, bool header)
{
	return this->result;
}

static size_t read_callback(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
	size_t retcode;

  /* in real-world cases, this would probably get this data differently
	as this fread() stuff is exactly what the library already would do
	by default internally */
	retcode = fread(ptr, size, nmemb, stream);

	std::cout << "retcode: " << retcode << std::endl;

	return retcode;
}

std::string& CMailBox::doSMTPUpload(std::string server, std::string login, std::string password, std::string filename) {
}

std::string& CMailBox::doHTTPUpload(std::string url, std::string filename, bool header) {


	return this->result;
}

void CMailBox::requestComplete()
{
//	LOG_ENTER("Mailbox::requestComplete");
//	if (getState() == DownloadIP)
//		setState(DownloadDone);
	if(buffer)
		this->result = std::string(buffer);
	else
		this->result="";
//	parseResponse();
}
std::string CMailBox::getMailbox() const
{
        return mailbox;
}
std::string CMailBox::getUser() const
{
	return user;
}

std::string CMailBox::getPassword() const
{
	return password;
}

std::string CMailBox::escape(std::string q)
{
}

std::string CMailBox::unescape(std::string q)
{
}

std::string CMailBox::getFileCRC() {
	return fileCRC;
}

std::string CMailBox::getSegCRC(std::string filename) {
// 	LOG(Log::Info, boost::format("Licze CRC"));
	return segCRC;
}

void CMailBox::calculateFileCRC(std::string filename) {
}

size_t CMailBox::_writeData(void *buffer, size_t size, size_t nmem, void *ptr)
{
}

size_t CMailBox::writeData(void *buffer, size_t size, size_t nmem)
{

}

void CMailBox::addHeader(const EmailHeader &hdr)
{
	headers.push_back(hdr);
}

void CMailBox::addHeaderLink(std::string link)
{
}

void CMailBox::addPostData(std::string field, std::string value )
{
}

void CMailBox::clearHeaders()
{
	headers.clear();
}



std::string CMailBox::getLink(int seg) {

}

int CMailBox::downloadSeg() {

}

int CMailBox::downloadSegDone() {

}

int CMailBox::checkHeaders(int numOfSegments) {

}

unsigned int
CMailBox::countAvailableSegments(unsigned int segment) {

}

unsigned int CMailBox::checkAvailableSegment(unsigned int segment) {

}
unsigned int CMailBox::getDownloadSpeed() const
{

}
unsigned int CMailBox::getUploadSpeed() const
{

}
int CMailBox::pauseDownload() {

}
int CMailBox::unpauseDownload() {

}
