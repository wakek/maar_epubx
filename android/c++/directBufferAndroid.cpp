#include <jni.h>
#include <stdlib.h>

extern "C" JNIEXPORT jobject JNICALL Java_com_wakek_ebook_1toolkit_ByteBufferHelper_newDirectBuffer(JNIEnv *env, jclass cls, jlong ptr, jlong size)
{
    return env->NewDirectByteBuffer(reinterpret_cast<void *>(static_cast<size_t>(ptr)), size);
}

extern "C" JNIEXPORT jlong JNICALL Java_com_wakek_ebook_1toolkit_ByteBufferHelper_malloc(JNIEnv *env, jclass cls, jlong size)
{
    return static_cast<jlong>(reinterpret_cast<size_t>(malloc(size)));
}

extern "C" JNIEXPORT void JNICALL Java_com_wakek_ebook_1toolkit_ByteBufferHelper_free(JNIEnv *env, jclass cls, jlong ptr)
{
    free(reinterpret_cast<void *>(static_cast<size_t>(ptr)));
}
