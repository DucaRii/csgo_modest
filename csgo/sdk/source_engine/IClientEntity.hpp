#pragma once

using CBaseHandle = unsigned long;

class IClientUnknown;
class ClientClass;
class bf_read;

class IClientNetworkable
{
public:
	virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual void Release() = 0;
	virtual ClientClass* GetClientClass() = 0;
	virtual void NotifyShouldTransmit( int state ) = 0;
	virtual void OnPreDataChanged( int updateType ) = 0;
	virtual void OnDataChanged( int updateType ) = 0;
	virtual void PreDataUpdate( int updateType ) = 0;
	virtual void PostDataUpdate( int updateType ) = 0;
	virtual void __unkn() = 0;
	virtual bool IsDormant() = 0;
	virtual int EntIndex() const = 0;
	virtual void ReceiveMessage( int classID, bf_read& msg ) = 0;
	virtual void* GetDataTableBasePtr() = 0;
	virtual void SetDestroyedOnRecreateEntities() = 0;
};

typedef unsigned short ClientShadowHandle_t;
typedef unsigned short ClientRenderHandle_t;
typedef unsigned short ModelInstanceHandle_t;

class IClientRenderable
{
public:
	virtual IClientUnknown* GetIClientUnknown() = 0;
	virtual math::vec3_t& GetRenderOrigin( void ) = 0;
	virtual math::vec3_t& GetRenderAngles( void ) = 0;
	virtual bool ShouldDraw( void ) = 0;
	virtual int GetRenderFlags( void ) = 0;
	virtual void Unused( void ) const {}
	virtual ClientShadowHandle_t GetShadowHandle() const = 0;
	virtual ClientRenderHandle_t& RenderHandle() = 0;
	virtual const void* GetModel() const = 0;
	virtual int DrawModel( int flags, const uint8_t& instance ) = 0;
	virtual int GetBody() = 0;
	virtual void GetColorModulation( float* color ) = 0;
	virtual bool LODTest() = 0;
	virtual bool SetupBones( math::matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime ) = 0;
	virtual void SetupWeights( const math::matrix3x4_t* pBoneToWorld, int nFlexWeightCount, float* pFlexWeights,
							   float* pFlexDelayedWeights ) = 0;
	virtual void DoAnimationEvents( void ) = 0;
	virtual void* GetPVSNotifyInterface() = 0;
	virtual void GetRenderBounds( math::vec3_t& mins, math::vec3_t& maxs ) = 0;
	virtual void GetRenderBoundsWorldspace( math::vec3_t& mins, math::vec3_t& maxs ) = 0;
	virtual void GetShadowRenderBounds( math::vec3_t& mins, math::vec3_t& maxs, int shadowType ) = 0;
	virtual bool ShouldReceiveProjectedTextures( int flags ) = 0;
	virtual bool GetShadowCastDistance( float* pDist, int shadowType ) const = 0;
	virtual bool GetShadowCastDirection( math::vec3_t* pDirection, int shadowType ) const = 0;
	virtual bool IsShadowDirty() = 0;
	virtual void MarkShadowDirty( bool bDirty ) = 0;
	virtual IClientRenderable* GetShadowParent() = 0;
	virtual IClientRenderable* FirstShadowChild() = 0;
	virtual IClientRenderable* NextShadowPeer() = 0;
	virtual int ShadowCastType() = 0;
	virtual void CreateModelInstance() = 0;
	virtual ModelInstanceHandle_t GetModelInstance() = 0;
	virtual const math::matrix3x4_t& RenderableToWorldTransform() = 0;
	virtual int LookupAttachment( const char* pAttachmentName ) = 0;
	virtual bool GetAttachment( int number, math::vec3_t& origin, math::vec3_t& angles ) = 0;
	virtual bool GetAttachment( int number, math::matrix3x4_t& matrix ) = 0;
	virtual float* GetRenderClipPlane( void ) = 0;
	virtual int GetSkin() = 0;
	virtual void OnThreadedDrawSetup() = 0;
	virtual bool UsesFlexDelayedWeights() = 0;
	virtual void RecordToolMessage() = 0;
	virtual bool ShouldDrawForSplitScreenUser( int nSlot ) = 0;
	virtual uint8_t OverrideAlphaModulation( uint8_t nAlpha ) = 0;
	virtual uint8_t OverrideShadowAlphaModulation( uint8_t nAlpha ) = 0;
};


class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle( const CBaseHandle& handle ) = 0;
	virtual const CBaseHandle& GetRefEHandle() const = 0;
};

class ICollideable;
class IClientNetworkable;
class IClientRenderable;
class IClientEntity;
class C_BaseEntity;
class IClientThinkable;
class IClientAlphaProperty;

class ICollideable
{
public:
	virtual void pad0();
	virtual math::vec3_t& OBBMins() const;
	virtual math::vec3_t& OBBMaxs() const;
};

class IClientUnknown : public IHandleEntity
{
public:
	virtual ICollideable* GetCollideable() = 0;
	virtual IClientNetworkable* GetClientNetworkable() = 0;
	virtual IClientRenderable* GetClientRenderable() = 0;
	virtual IClientEntity* GetIClientEntity() = 0;
	virtual C_BaseEntity* GetBaseEntity() = 0;
	virtual IClientThinkable* GetClientThinkable() = 0;
	virtual IClientAlphaProperty* GetClientAlphaProperty() = 0;
};

enum
{
	FL_ONGROUND = 1 << 0,
	FL_DUCKING = 1 << 1,
	FL_WATERJUMP = 1 << 2,
	FL_FROZEN = 1 << 5,
	FL_FAKECLIENT = 1 << 8,
};

enum
{
	ALIVE = 0,
	DYING,
	DEAD,
	RESPAWNABLE,
	DISCARDBODY,
};

class IClientEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable
{
public:
	void Release() override = 0;
};