#ifndef MOORHUNTHASHDECODER_H__
#define MOORHUNTHASHDECODER_H__


#include "hashdecoder.h"
#include "tools.h"



class MoorhuntHashDecoder : public HashDecoder {
        public:
                ~MoorhuntHashDecoder() {}

        public:
                virtual Hash* decode(const QString& hashcode);
};

class MoorhuntHashEncoder {
            std::string myFilename;
            int myCRC;
                std::string myCleanCRC;
            int myFileSize;
            bool myRound;
            bool myRandName;
            int mySegmentCount;
            int myMinSize;
            int myMaxSize;
            std::string myDownloadPassword;
            int myMirrors;
            // tutaj lista mirrorow
            std::string myAvartLink;
            std::string myEditPassword;
            std::string myFor;
            std::string myFullDescriptionLink;
            std::string myFullTitle;
            std::string myUploader;
            std::string myComment;
                std::vector<std::string> mailboxes;


        public:
                MoorhuntHashEncoder();
                ~MoorhuntHashEncoder();
                void setFilename(std::string data) { myFilename = data; };
                void setCRC(std::string data) { myCleanCRC = data; };
                void setFileSize(int data) { myFileSize = data; };
                void setRound(bool data) { myRound = data; };
                void setRandName(bool data) { myRandName = data; };
                void setSegmentCount(int data) { mySegmentCount = data; };
                void setSegSize(int data) { myMinSize = data; myMaxSize = data; };
                void setDownloadPassword(std::string data) { myDownloadPassword = data.c_str(); };
                void setMirrors(int data) { myMirrors = data; };
                void setAvartLink(std::string data) { myAvartLink = data; };
                void setEditPassword(std::string data) { myEditPassword = data.c_str(); };

                const bool decode(QString hashcode);
                const std::string encodeClean();
                const std::string encodeWithNewMirror();
                const std::string addNewMirror(std::string editpassword, std::string hashcode, std::string mailbox, std::string password);

                std::string getMD5(unsigned char *string);
};


#endif // MOORHUNTHASHDECODER_H__


