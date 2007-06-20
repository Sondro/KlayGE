// RenderEngine.cpp
// KlayGE 渲染引擎类 实现文件
// Ver 3.6.0
// 版权所有(C) 龚敏敏, 2003-2007
// Homepage: http://klayge.sourceforge.net
//
// 3.6.0
// 去掉了RenderTarget，直接使用FrameBuffer (2007.6.20)
//
// 3.3.0
// 统一了RenderState (2006.5.21)
//
// 2.8.0
// 简化了StencilBuffer相关操作 (2005.7.20)
//
// 2.7.1
// ViewMatrix和ProjectionMatrix改为const (2005.7.10)
//
// 2.4.0
// 增加了NumPrimitivesJustRendered和NumVerticesJustRendered (2005.3.21)
//
// 2.0.3
// 优化了RenderEffect的设置 (2004.2.16)
// 去掉了VO_2D (2004.3.1)
// 去掉了SoftwareBlend (2004.3.10)
//
// 2.0.0
// 初次建立(2003.10.1)
//
// 修改记录
//////////////////////////////////////////////////////////////////////////////////

#include <KlayGE/KlayGE.hpp>
#include <KlayGE/Math.hpp>
#include <KlayGE/Viewport.hpp>
#include <KlayGE/FrameBuffer.hpp>
#include <KlayGE/GraphicsBuffer.hpp>
#include <KlayGE/RenderEffect.hpp>

#include <KlayGE/RenderEngine.hpp>

namespace KlayGE
{
	class NullRenderEngine : public RenderEngine
	{
	public:
		std::wstring const & Name() const
		{
			static std::wstring const name(L"Null Render Engine");
			return name;
		}

		void StartRendering()
		{
		}

		void BeginFrame()
		{
		}
		void EndFrame()
		{
		}

		void Clear(uint32_t /*masks*/, Color const & /*clr*/, float /*depth*/, int32_t /*stencil*/)
		{
		}

		void CreateRenderWindow(std::string const & /*name*/, RenderSettings const & /*settings*/)
		{
		}

		void SetStateObjects(RenderStateObject const & /*rs_obj*/, ShaderObject const & /*shader_obj*/)
		{
		}

		uint16_t StencilBufferBitDepth()
		{
			return 0;
		}

		void ScissorRect(uint32_t /*x*/, uint32_t /*y*/, uint32_t /*width*/, uint32_t /*height*/)
		{
		}

		float4 TexelToPixelOffset() const
		{
			return float4(0, 0, 0, 0);
		}

		void Resize(uint32_t /*width*/, uint32_t /*height*/)
		{
		}

		bool FullScreen() const
		{
			return false;
		}

		void FullScreen(bool /*fs*/)
		{
		}

	private:
		void DoBindFrameBuffer(FrameBufferPtr /*fb*/)
		{
		}

		void DoRender(RenderTechnique const & /*tech*/, RenderLayout const & /*rl*/)
		{
		}

		void FillRenderDeviceCaps()
		{
		}
	};

	// 构造函数
	/////////////////////////////////////////////////////////////////////////////////
	RenderEngine::RenderEngine()
	{
	}

	// 析构函数
	/////////////////////////////////////////////////////////////////////////////////
	RenderEngine::~RenderEngine()
	{
	}

	// 返回空对象
	/////////////////////////////////////////////////////////////////////////////////
	RenderEnginePtr RenderEngine::NullObject()
	{
		static RenderEnginePtr obj(new NullRenderEngine);
		return obj;
	}

	// 设置当前渲染目标
	/////////////////////////////////////////////////////////////////////////////////
	void RenderEngine::BindFrameBuffer(FrameBufferPtr fb)
	{
		if (cur_frame_buffer_)
		{
			cur_frame_buffer_->OnUnbind();
		}

		if (!fb)
		{
			cur_frame_buffer_ = default_frame_buffer_;
		}
		else
		{
			cur_frame_buffer_ = fb;
		}

		cur_frame_buffer_->OnBind();

		this->DoBindFrameBuffer(cur_frame_buffer_);
	}

	// 获取当前渲染目标
	/////////////////////////////////////////////////////////////////////////////////
	FrameBufferPtr RenderEngine::CurFrameBuffer() const
	{
		return cur_frame_buffer_;
	}

	// 获取默认渲染目标
	/////////////////////////////////////////////////////////////////////////////////
	FrameBufferPtr RenderEngine::DefaultFrameBuffer() const
	{
		return default_frame_buffer_;
	}

	// 渲染一个vb
	/////////////////////////////////////////////////////////////////////////////////
	void RenderEngine::Render(RenderTechnique const & tech, RenderLayout const & rl)
	{
		this->DoRender(tech, rl);
	}

	// 上次Render()所渲染的图元数
	/////////////////////////////////////////////////////////////////////////////////
	size_t RenderEngine::NumPrimitivesJustRendered()
	{
		size_t const ret = numPrimitivesJustRendered_;
		numPrimitivesJustRendered_ = 0;
		return ret;
	}

	// 上次Render()所渲染的顶点数
	/////////////////////////////////////////////////////////////////////////////////
	size_t RenderEngine::NumVerticesJustRendered()
	{
		size_t const ret = numVerticesJustRendered_;
		numVerticesJustRendered_ = 0;
		return ret;
	}

	// 获取渲染设备能力
	/////////////////////////////////////////////////////////////////////////////////
	RenderDeviceCaps const & RenderEngine::DeviceCaps() const
	{
		return caps_;
	}
}
