//
// Copyright (c) 2024 Yellow. All rights reserved.
//

#ifndef LEARNAV_IGLCONTEXT_H
#define LEARNAV_IGLCONTEXT_H

#include <memory>

#ifdef _WIN32
#include <glad/glad.h>
#endif
#include <QOffscreenSurface>
#include <QOpenGLContext>
#include <QThread>

namespace av {

class GLContext {
public:
    explicit GLContext(void* sharedGLContext);
    virtual ~GLContext();

    bool Initialize();
    void Destroy();
    void MakeCurrent();
    void DoneCurrent();
    void* GetSharedGLContext() { return m_sharedGLContext; }

private:
    void CreateOnGUIThread(bool* created);

    QOpenGLContext* m_sharedGLContext{nullptr};
    // 每个线程需要独立的 QOpenGLContext/QOffscreenSurface，否则 Qt 拒绝
    // 跨线程 makeCurrent ("Cannot make QOpenGLContext current in a different thread")。
    // 用 thread_local 保证各线程拿到自己的 context。
    QOpenGLContext*& tlsContext();
    QOffscreenSurface*& tlsSurface();
};

}  // namespace av

#endif  // LEARNAV_IGLCONTEXT_H
