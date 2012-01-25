#include "CEvent.h"


CEvent::CEvent()
{
}

CEvent::~CEvent()
{
}

void CEvent::OnEvent( SDL_Event* Event )
{
    switch ( Event->type )
    {
        //Gain/lose mouse focus, Minimize/restore window
        case SDL_ACTIVEEVENT:
        {
            switch ( Event->active.state )
            {
                case SDL_APPMOUSEFOCUS:
                {

                    if ( Event->active.gain )
                    {
                        OnMouseFocus();
                    }

                    else
                    {
                        OnMouseBlur();
                    }

                }

                case SDL_APPINPUTFOCUS:
                {

                    if ( Event->active.gain )
                    {
                        OnInputFocus();
                    }

                    else
                    {
                        OnInputBlur();
                    }

                }

                case SDL_APPACTIVE:
                {

                    if ( Event->active.gain )
                    {
                        OnRestore();
                    }

                    else
                    {
                        OnMinimize();
                    }

                }

            }

            break;
        }

        case SDL_KEYDOWN:
        {
            OnKeyDown( Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode );
            break;
        }

        case SDL_KEYUP:
        {
            OnKeyUp( Event->key.keysym.sym, Event->key.keysym.mod, Event->key.keysym.unicode );
            break;
        }

        case SDL_MOUSEMOTION:
        {
            OnMouseMove( Event->motion.x,
                         Event->motion.y,
                         Event->motion.xrel,
                         Event->motion.yrel,
                         //bitwise-AND of the event's motion.state to determine which button is pressed
                         ( Event->motion.state & SDL_BUTTON( SDL_BUTTON_LEFT ) ) != 0,
                         ( Event->motion.state & SDL_BUTTON( SDL_BUTTON_RIGHT ) ) != 0,
                         ( Event->motion.state & SDL_BUTTON( SDL_BUTTON_MIDDLE ) ) != 0
                       );
            break;
        }

        case SDL_MOUSEBUTTONDOWN:
        {
            switch ( Event->button.button )
            {

                case SDL_BUTTON_LEFT:
                {
                    OnLButtonDown( Event->button.x, Event->button.y );
                    break;
                }

                case SDL_BUTTON_RIGHT:
                {
                    OnRButtonDown( Event->button.x, Event->button.y );
                    break;
                }

                case SDL_BUTTON_MIDDLE:
                {
                    OnMButtonDown( Event->button.x, Event->button.y );
                    break;
                }

            }

            break;
        }

        case SDL_MOUSEBUTTONUP:
        {
            switch ( Event->button.button )
            {

                case SDL_BUTTON_LEFT:
                {
                    OnLButtonUp( Event->button.x, Event->button.y );
                    break;
                }

                case SDL_BUTTON_RIGHT:
                {
                    OnRButtonUp( Event->button.x, Event->button.y );
                    break;
                }

                case SDL_BUTTON_MIDDLE:
                {
                    OnMButtonUp( Event->button.x, Event->button.y );
                    break;
                }

            }

            break;
        }

        case SDL_QUIT:
        {
            OnExit();
            break;
        }

        //Unhandled window manager event
        case SDL_SYSWMEVENT:
        {
            //Do nothing?
            break;
        }

        //Resize the window
        case SDL_VIDEORESIZE:
        {
            OnResize( Event->resize.w, Event->resize.h );
            break;
        }

        //Screen modified outside of the window manager (redraw)
        case SDL_VIDEOEXPOSE:
        {
            OnExpose();
            break;
        }

        default:
        {
            OnUser( Event->user.type,
                    Event->user.code,
                    Event->user.data1,
                    Event->user.data2 );
            break;
        }

    }
}


void CEvent::OnInputFocus() {}

void CEvent::OnInputBlur () {}


void CEvent::OnKeyDown   ( SDLKey sym, SDLMod mod, Uint16 unicode ) {}

void CEvent::OnKeyUp     ( SDLKey sym, SDLMod mod, Uint16 unicode ) {}


void CEvent::OnMouseFocus () {}

void CEvent::OnMouseBlur  () {}

void CEvent::OnMouseMove  ( int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle ) {}

void CEvent::OnMouseWheel ( bool Up, bool Down ) {}

void CEvent::OnLButtonDown ( int mX, int mY ) {}

void CEvent::OnLButtonUp   ( int mX, int mY ) {}

void CEvent::OnRButtonDown ( int mX, int mY ) {}

void CEvent::OnRButtonUp   ( int mX, int mY ) {}

void CEvent::OnMButtonDown ( int mX, int mY ) {}

void CEvent::OnMButtonUp   ( int mX, int mY ) {}


void CEvent::OnMinimize () {}

void CEvent::OnRestore  () {}

void CEvent::OnResize   ( int w, int h ) {}

void CEvent::OnExpose   () {}

void CEvent::OnUser     ( Uint8 type, int code, void* data1, void* data2 ) {}

void CEvent::OnExit     () {}






