#ifdef WIN32
#pragma message("Compiling precompiled header.\n")

#include <windows.h>
#include <winsock.h>
#include <mmsystem.h>
#endif

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <ctime>
#include <sstream>

// Forward declarations
class CAclRightName;
struct SAclRequest;

// SDK includes
#include "MTAPlatform.h"
#define SHARED_UTIL_WITH_FAST_HASH_MAP
#include "SharedUtil.h"
#include <xml/CXML.h>
#include <xml/CXMLNode.h>
#include <xml/CXMLFile.h>
#include <xml/CXMLAttributes.h>
#include <xml/CXMLAttribute.h>
#include "CVector.h"
#include "CSphere.h"
#include "CBox.h"
#include "CMatrix.h"
#include "CQuat.h"
#include "Enums.h"
#include <bochs_internal/crc32.h>
#include "CChecksum.h"
#include "CIdArray.h"

// Packet includes
#include "net/Packets.h"
#include "packets/CCameraSyncPacket.h"
#include "packets/CChatEchoPacket.h"
#include "packets/CCommandPacket.h"
#include "packets/CConsoleEchoPacket.h"
#include "packets/CCustomDataPacket.h"
#include "packets/CDebugEchoPacket.h"
#include "packets/CDetonateSatchelsPacket.h"
#include "packets/CEntityAddPacket.h"
#include "packets/CEntityRemovePacket.h"
#include "packets/CExplosionSyncPacket.h"
#include "packets/CFireSyncPacket.h"
#include "packets/CKeysyncPacket.h"
#include "packets/CLuaEventPacket.h"
#include "packets/CLuaPacket.h"
#include "packets/CElementRPCPacket.h"
#include "packets/CMapInfoPacket.h"
#include "packets/CObjectStartSyncPacket.h"
#include "packets/CObjectStopSyncPacket.h"
#include "packets/CObjectSyncPacket.h"
#include "packets/CPacket.h"
#include "packets/CPedStartSyncPacket.h"
#include "packets/CPedStopSyncPacket.h"
#include "packets/CPedSyncPacket.h"
#include "packets/CPedWastedPacket.h"
#include "packets/CPickupHideShowPacket.h"
#include "packets/CPickupHitConfirmPacket.h"
#include "packets/CPlayerChangeNickPacket.h"
#include "packets/CPlayerClothesPacket.h"
#include "packets/CPlayerConnectCompletePacket.h"
#include "packets/CPlayerDisconnectedPacket.h"
#include "packets/CPlayerJoinCompletePacket.h"
#include "packets/CPlayerJoinDataPacket.h"
#include "packets/CPlayerJoinPacket.h"
#include "packets/CPlayerListPacket.h"
#include "packets/CPlayerPuresyncPacket.h"
#include "packets/CPlayerQuitPacket.h"
#include "packets/CPlayerSpawnPacket.h"
#include "packets/CPlayerStatsPacket.h"
#include "packets/CPlayerTimeoutPacket.h"
#include "packets/CPlayerWastedPacket.h"
#include "packets/CProjectileSyncPacket.h"
#include "packets/CResourceStartPacket.h"
#include "packets/CResourceStopPacket.h"
#include "packets/CResourceClientScriptsPacket.h"
#include "packets/CReturnSyncPacket.h"
#include "packets/CServerTextItemPacket.h"
#include "packets/CUpdateInfoPacket.h"
#include "packets/CUnoccupiedVehicleStartSyncPacket.h"
#include "packets/CUnoccupiedVehicleStopSyncPacket.h"
#include "packets/CUnoccupiedVehicleSyncPacket.h"
#include "packets/CUnoccupiedVehiclePushPacket.h"
#include "packets/CVehicleDamageSyncPacket.h"
#include "packets/CVehicleInOutPacket.h"
#include "packets/CVehiclePuresyncPacket.h"
#include "packets/CLightsyncPacket.h"
#include "packets/CVehicleResyncPacket.h"
#include "packets/CVehicleSpawnPacket.h"
#include "packets/CVehicleTrailerPacket.h"
#include "packets/CVoiceDataPacket.h"
#include "packets/CVoiceEndPacket.h"

// Lua function definition includes
#include "luadefs/CLuaACLDefs.h"
#include "luadefs/CLuaCameraDefs.h"
#include "luadefs/CLuaDefs.h"
#include "luadefs/CLuaElementDefs.h"
#include "luadefs/CLuaFileDefs.h"
#include "luadefs/CLuaHTTPDefs.h"
#include "luadefs/CLuaHandlingDefs.h"
#include "luadefs/CLuaPickupDefs.h"
#include "luadefs/CLuaResourceDefs.h"
#include "luadefs/CLuaTextDefs.h"
#include "luadefs/CLuaWorldDefs.h"
#include "luadefs/CLuaVoiceDefs.h"
#include "luadefs/CLuaXMLDefs.h"

// Lua includes
#include "lua/LuaCommon.h"
#include "lua/CLuaMain.h"
#include "CEasingCurve.h"
#include "lua/CLuaFunctionParseHelpers.h"
#include "CScriptArgReader.h"
#include "lua/CLuaManager.h"
#include "lua/CLuaTimerManager.h"
#include "lua/CLuaTimer.h"
#include "lua/CLuaFunctionDefinitions.h"
#include "lua/CLuaModuleManager.h"
#include "lua/CLuaArgument.h"
#include "lua/CLuaCFunctions.h"
#include "lua/CLuaArguments.h"
#include "lua/CLuaCallback.h"
#include "lua/LuaUtils.h"

// Sim includes
#include "net/CSimControl.h"

// Shared includes
#include "TInterpolation.h"
#include "CPositionRotationAnimation.h"
#include "CLatentTransferManager.h"

// Logic includes
#include "ASE.h"
#include "ASEQuerySDK.h"
#include "CAccessControlList.h"
#include "CAccessControlListGroup.h"
#include "CAccessControlListManager.h"
#include "CAccessControlListRight.h"
#include "CAccount.h"
#include "CAccountManager.h"
#include "CAclRightName.h"
#include "CBan.h"
#include "CBanManager.h"
#include "CBandwidthSettings.h"
#include "CBlendedWeather.h"
#include "CBlip.h"
#include "CBlipManager.h"
#include "CCameraSpatialDatabase.h"
#include "CClient.h"
#include "CClock.h"
#include "CColCallback.h"
#include "CColCircle.h"
#include "CColCuboid.h"
#include "CColManager.h"
#include "CColPolygon.h"
#include "CColRectangle.h"
#include "CColShape.h"
#include "CColSphere.h"
#include "CColTube.h"
#include "CCommandFile.h"
#include "CCommandLineParser.h"
#include "CCommon.h"
#include "CConfig.h"
#include "CConnectHistory.h"
#include "CConsole.h"
#include "CConsoleClient.h"
#include "CConsoleCommand.h"
#include "CConsoleCommands.h"
#include "CCustomData.h"
#include "CDummy.h"
#include "CElement.h"
#include "CElementDeleter.h"
#include "CElementGroup.h"
#include "CElementIDs.h"
#include "CElementRefManager.h"
#include "CEvents.h"
#include "CGame.h"
#include "CGroups.h"
#include "CHTTPD.h"
#include "CHandlingEntry.h"
#include "CHandlingManager.h"
#include "CKeyBinds.h"
#include "CLanBroadcast.h"
#include "CLightsyncManager.h"
#include "CLogger.h"
#include "CMainConfig.h"
#include "CMapEvent.h"
#include "CMapEventManager.h"
#include "CMapManager.h"
#include "CMarker.h"
#include "CMarkerManager.h"
#include "CObject.h"
#include "CObjectManager.h"
#include "CObjectSync.h"
#include "CPacketTranslator.h"
#include "CPad.h"
#include "CPed.h"
#include "CPedManager.h"
#include "CPedSync.h"
#include "CPerfStatManager.h"
#include "CPerPlayerEntity.h"
#include "CPickup.h"
#include "CPickupManager.h"
#include "CPlayer.h"
#include "CPlayerCamera.h"
#include "CPlayerClothes.h"
#include "CPlayerManager.h"
#include "CPlayerStats.h"
#include "CPlayerTasks.h"
#include "CPlayerTextManager.h"
#include "CRPCFunctions.h"
#include "CRadarArea.h"
#include "CRadarAreaManager.h"
#include "CRegisteredCommands.h"
#include "CRegistryManager.h"
#include "CRegistry.h"
#include "CRemoteCalls.h"
#include "CResource.h"
#include "CResourceChecker.h"
#include "CResourceClientConfigItem.h"
#include "CResourceClientFileItem.h"
#include "CResourceClientScriptItem.h"
#include "CResourceConfigItem.h"
#include "CResourceFile.h"
#include "CResourceHTMLItem.h"
#include "CResourceManager.h"
#include "CResourceMapItem.h"
#include "CResourceScriptItem.h"
#include "CScriptDebugging.h"
#include "CScriptFile.h"
#include "CSettings.h"
#include "CSpatialDatabase.h"
#include "CTeam.h"
#include "CTeamManager.h"
#include "CTextDisplay.h"
#include "CTextItem.h"
#include "CTickRateSettings.h"
#include "CUnoccupiedVehicleSync.h"
#include "CVehicle.h"
#include "CVehicleColorManager.h"
#include "CVehicleDefaultColors.h"
#include "CVehicleManager.h"
#include "CVehicleNames.h"
#include "CVehicleUpgrades.h"
#include "CWater.h"
#include "CWaterManager.h"
#include "CWeaponNames.h"
#include "CWhoWas.h"
#include "CXMLConfig.h"
#include "CZoneNames.h"
#include "TaskNames.h"
#include "Utils.h"
#include "logic/CWeaponStat.h"
#include "logic/CWeaponStatManager.h"
#include "logic/CBuildingRemoval.h"
#include "logic/CBuildingRemovalManager.h"

#include "CStaticFunctionDefinitions.h"

// Utility includes
#include "utils/CHTTPClient.h"
#include "utils/CHTTPRequest.h"
#include "utils/CHTTPResponse.h"
#include "utils/CTCP.h"
#include "utils/CTCPClientSocket.h"
#include "utils/CTCPClientSocketImpl.h"
#include "utils/CTCPImpl.h"
#include "utils/CTCPServerSocket.h"
#include "utils/CTCPServerSocketImpl.h"
#include "utils/CTCPSocket.h"
#include "utils/CTCPSocketImpl.h"
#include "utils/CZipMaker.h"
#include <base64.h>

// Module includes
#include "CServer.h"
#include "Config.h"
#define SHOW_SELF_COMPILE_WARNING
#include "../../version.h"


#if defined(__GNUC__) && (__GNUC__ >= 3)
    namespace __gnu_cxx
    {
        template <>
        struct hash < CLuaArguments* >
        {
            size_t operator()( const CLuaArguments* pArguments ) const
            {
                return (size_t)pArguments;
            }
        };

        template <>
        struct hash < const void* >
        {
            size_t operator()( const void* pArguments ) const
            {
                return (size_t)pArguments;
            }
        };
    }
#endif
