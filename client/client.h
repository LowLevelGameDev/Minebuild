#pragma once
#include <client/interface.hpp>

#include <thread>
#include <stdio.h>

#include <polygl.h>

/*
* Relies on interface
* renders changes signified by server to the client
* updates server with any client interaction
*/
class Client {
  typedef Client this_t;

  Interface mserver;
  ::poly_ctx_t *mctx;
  ::poly_error_t merr;

  bool m_exit = false;
  std::thread renderer;
public:
  Client() = default;
  Client(Client&&) = delete;
  Client(const Client&) = delete;
  ~Client() {
    this->renderer.join();

    // destroy window
    ::pwin_delete(this->mctx);

    // destroy device interface
    ::pdev_delete(this->mctx);

    // de-initalize library
    ::poly_destroy(this->mctx);
  }

  static void m_RenderMinebuild(this_t *_this) {
    // initalize shader pipeline
    ::poly_pipe_t *pipe;
    ::ppipe_create(_this->mctx,&pipe,"client/shaders/simple_shader.vert.spv","client/shaders/simple_shader.frag.spv");

    // initalize renderer
    ::poly_rctx_t *rctx;
    uint32_t maxFrames = 2;
    ::prctx_create(&rctx,pipe,_this->mctx,maxFrames);

    // main
    uint32_t currentFrame = 0;
    while (!::pwin_should_close(_this->mctx)) {
      ::pwin_set_ctx(_this->mctx);
      ::pwin_poll();
      ::poly_aquire_frame(rctx,pipe,_this->mctx,currentFrame);
      currentFrame = (currentFrame + 1) % maxFrames;
    }

    // idle before destroying objects
    ::pdev_idle(_this->mctx); // ensures all device threads are done

    // destroy renderer
    ::prctx_delete(rctx,pipe,_this->mctx);

    // destroy shader pipeline
    ::ppipe_delete(_this->mctx,pipe);
  }

  bool open(Interface&& server, long Width, long Height) {
    this->merr = ::poly_instance(&this->mctx, "Default Minebuild Client", "No Engine", true);
    if (this->merr != POLY_GOOD) {
      printf("%s    ", ::strpolyerr(this->merr));
      ::poly_destroy(this->mctx);
      return false;
    }

    // select device and create interface
    ::pdev_create(this->mctx,0);

    // initalize window
    ::pwin_create(this->mctx,Width,Height,1);
    
    this->renderer = std::thread(this_t::m_RenderMinebuild,this);

    return true;
  }
  // seed creation
  // (create world from seed, safe server holds copy)
  // user input
  // drawing
  // END
};


