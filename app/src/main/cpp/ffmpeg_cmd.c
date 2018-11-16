#include <jni.h>
#include "ffmpeg/ffmpeg.h"

JNIEXPORT jint JNICALL Java_com_frank_ffmpeg_FFmpegCmd_handle
        (JNIEnv *env, jclass obj, jobjectArray commands){
    int argc = (*env)->GetArrayLength(env, commands);//获取字符串长度
    char **argv = (char**)malloc(argc * sizeof(char*));//申请内存空间，**argv存得内存空间首地址（单星指向内容，双星指向地址）
    int i;
    int result;
    for (i = 0; i < argc; i++) {
        jstring jstr = (jstring) (*env)->GetObjectArrayElement(env, commands, i);//逐一取出字符串
        char* temp = (char*) (*env)->GetStringUTFChars(env, jstr, 0);//转化成C支持的字符串
        argv[i] = malloc(1024);
        strcpy(argv[i], temp);//后字符串复制到前字符串
        (*env)->ReleaseStringUTFChars(env, jstr, temp);//释放字符串内存
    }
    //执行ffmpeg命令
    result =  run(argc, argv);
    //释放内存
    for (i = 0; i < argc; i++) {
        free(argv[i]);
    }
    free(argv);
    return result;
}