/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/deathmatch/logic/CSingularFileDownload.h
*  PURPOSE:     Header for singular file download
*  DEVELOPERS:  Kevin Whiteside <>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/


#ifndef CSINGULARFILEDOWNLOAD_H
#define CSINGULARFILEDOWNLOAD_H

#ifndef _WINDOWS_

#define WIN32_LEAN_AND_MEAN     // Exclude all uncommon functions from windows.h to reduce build time by 100ms

#include <windows.h>
#endif

#include <bochs_internal/crc32.h>
#include "CChecksum.h"

class CSingularFileDownload
{
    
public:
                        CSingularFileDownload           ( CResource* pResource, const char* szName, const char* szNameShort, SString strHTTPURL, CChecksum checksum );
                        ~CSingularFileDownload          ( void );

        static void     ProgressCallBack                ( double sizeJustDownloaded, double totalDownloaded, char * data, size_t dataLength, void * obj, bool complete, int error );

        bool            DoesClientAndServerChecksumMatch ( void );

        inline const char*      GetName                         ( void ) { return m_szName; };
        inline const char*      GetShortName                    ( void ) { return m_szNameShort; };

        inline CResource*       GetResource                     ( void ) { return m_pResource; };

        inline void             SetComplete                     ( void ) { m_bComplete = true; };
        inline bool             GetComplete                     ( void ) { return m_bComplete; };

        void                    CallFinished                    ( void );

        // CRC-based methods
        CChecksum               GenerateClientChecksum          ( void );

        CChecksum               GetLastClientChecksum           ( void );
    
        CChecksum               GetProvidedChecksum             ( void );
        void                    SetProvidedChecksum             ( CChecksum providedChecksum );

protected:

    char*               m_szName;
    char*               m_szNameShort;

    CResource*          m_pResource;

    bool                m_bComplete;

    CChecksum           m_LastClientChecksum;
    CChecksum           m_ProvidedChecksum;

};

#endif