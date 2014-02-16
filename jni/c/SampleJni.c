#include <stdio.h>
#include <jni.h>

JNIEnv* create_vm(char * class_path) {
	JavaVM* jvm;
	JNIEnv* env;
	JavaVMInitArgs args;
	JavaVMOption options[1];
	
	/* There is a new JNI_VERSION_1_4, but it doesn't add anything for the purposes of our example. */
	args.version = JNI_VERSION_1_6;
	args.nOptions = 1;
	options[0].optionString = class_path;
	args.options = options;
	args.ignoreUnrecognized = JNI_FALSE;

	JNI_CreateJavaVM(&jvm, (void **)&env, &args);
	return env;
}

void invoke_class(JNIEnv* env, char * class_name, char * method_name) {
 
	jclass helloWorldClass;
	jmethodID mainMethod;
	jobjectArray applicationArgs;
	jstring applicationArg0;

	helloWorldClass = (*env)->FindClass(env, class_name);

	mainMethod = (*env)->GetStaticMethodID(env, helloWorldClass, method_name, "([Ljava/lang/String;)V");

        //type of argument -> string[]
	applicationArgs = (*env)->NewObjectArray(env, 1, (*env)->FindClass(env, "java/lang/String"), NULL);
	//0th member of string array ->
        applicationArg0 = (*env)->NewStringUTF(env, "From-C-program");

	(*env)->SetObjectArrayElement(env, applicationArgs, 0, applicationArg0);


        printf("calling java method from c.....\n");
	(*env)->CallStaticVoidMethod(env, helloWorldClass, mainMethod, applicationArgs);
	
        printf("calling java method from c again.....\n");
	(*env)->CallStaticVoidMethod(env, helloWorldClass, mainMethod, applicationArgs);
}


int main(int argc, char **argv) {
printf("This program helps you call static methods present in java objects.. \n"); printf("\n");
	JNIEnv* env = create_vm("-Djava.class.path=../classes");

        char * className = "com/jni/Hello";
        char * methodName = "hi";
	invoke_class( env, className, methodName );
}


