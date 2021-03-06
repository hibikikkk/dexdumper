//
// Created by asus on 2016/8/16.
//

#ifndef HOOKMANAGER_CODERESOLVER_H
#define HOOKMANAGER_CODERESOLVER_H

#include <pthread.h>
#include <unordered_map>
#include "jni.h"
#include "art-member.h"
#include "DexCommons.h"
#include "dalvik/Object.h"
#include "dex_file.h"

typedef std::unordered_map<jfieldID ,u4> FieldMap;
typedef std::unordered_map<jmethodID ,u4> MethodMap;
#ifdef __cplusplus
extern "C" {
#endif
jint  getFieldOffset(JNIEnv *env,jclass thisClass,jobject field);
jint  getMethodVIdx(JNIEnv *env,jclass thisClass,jobject method);
#ifdef __cplusplus
}

art::DexFile *getRealDexFile(u4 declaring_class);

#define GET_ART_METHOD_MEMBER_VALUE(var_out,mem_name, method_id)\
 if(isKitkatArt()){\
ArtMethodKitkat* artMethod= reinterpret_cast<ArtMethodKitkat*>(reinterpret_cast<u1*>(method_id));\
var_out= artMethod->mem_name;\
} else if(isArtL()){\
ArtMethodLollipop* artMethod= reinterpret_cast<ArtMethodLollipop*>(reinterpret_cast<u1*>(method_id));\
var_out=  artMethod->mem_name;\
} else if(isArtLMr1()){\
ArtMethodLollipopMr1* artMethod= reinterpret_cast<ArtMethodLollipopMr1*>(reinterpret_cast<u1*>(method_id));\
var_out=  artMethod->mem_name;\
} else if(isArtNougat()){\
ArtMethodNougat* artMethod=reinterpret_cast<ArtMethodNougat*>(reinterpret_cast<u1*>(method_id));\
var_out=  artMethod->mem_name;\
}\
else{\
ArtMethodMarshmallow* artMethod= reinterpret_cast<ArtMethodMarshmallow*>(reinterpret_cast<u1*>(method_id));\
var_out=  artMethod->mem_name;\
}

class CodeResolver{
public:
    enum {
        UNDEFINED = 0xffffffff,
    };
private:
    enum RegisterType{
        TypeArray=0xffff+1,
        TypePrimitiveExtend = UNDEFINED - 4,
        TypeZero = UNDEFINED - 3,
        TypeException = UNDEFINED - 2,
        TypePrimitive = UNDEFINED - 1,
    };
    enum FileOpCode {
        nop=0,
        move=0x1,
        move16=0x2,
        move16L=0x3,
        moveW=0x4,
        move16W=0x5,
        move16LW=0x6,
        moveOb=0x7,
        moveOb16=0x8,
        moveOb16L=0x9,
        moveResult=0xa,
        moveResultW=0xb,
        moveResultOb=0xc,
        moveExcept=0xd,
        returnV=0xe,
        returnD=0xf,
        returnW=0x10,
        returnOb=0x11,
        const4=0x12,
        const16=0x13,
        const32=0x14,
        const16H=0x15,
        const16W=0x16,
        const32W=0x17,
        const64W=0x18,
        const16HW=0x19,
        constStr=0x1a,
        constStrJ=0x1b,
        constClass=0x1c,
        monitorEnter=0x1d,
        monitorExit=0x1e,
        checkCast=0x1f,
        instanceOf=0x20,
        arrayLen=0x21,
        newInstance=0x22,
        newArray=0x23,
        fillArray=0x24,
        fillArrayR=0x25,
        fillArrayData=0x26,
        throwD=0x27,
        goto8=0x28,
        goto16=0x29,
        goto32=0x2a,
        packedSwitch=0x2b,
        sparseSwitch=0x2c,
        //cmp-stub 2d-31
        ifEq=0x32,
        ifNe=0x33,
        ifLt=0x34,
        ifGe=0x35,
        ifGt=0x36,
        ifLe=0x37,
        ifEqz=0x38,
        ifNez=0x39,
        ifLtz=0x3a,
        ifGez=0x3b,
        ifGtz=0x3c,
        ifLez=0x3d,
        //stub 3e-43 unused
        aget=0x44,
        agetW=0x45,
        agetOb=0x46,
        agetBoolean=0x47,
        agetByte=0x48,
        agetChar=0x49,
        agetShort=0x4a,
        aput=0x4b,
        aputW=0x4c,
        aputOb=0x4d,
        aputBoolean=0x4e,
        aputByte=0x4f,
        aputChar=0x50,
        aputShort=0x51,
        iget=0x52,
        igetW=0x53,
        igetOb=0x54,
        igetBoolean=0x55,
        igetByte=0x56,
        igetChar=0x57,
        igetShort=0x58,
        iput=0x59,
        iputW=0x5a,
        iputOb=0x5b,
        iputBoolean=0x5c,
        iputByte=0x5d,
        iputChar=0x5e,
        iputShort=0x5f,
        sget=0x60,
        sgetW=0x61,
        sgetOb=0x62,
        sgetBoolean=0x63,
        sgetByte=0x64,
        sgetChar=0x65,
        sgetShort=0x66,
        sput=0x67,
        sputW=0x68,
        sputOb=0x69,
        sputBoolean=0x6a,
        sputByte=0x6b,
        sputChar=0x6c,
        sputShort=0x6d,
        invokeVirtual=0x6e,
        invokeSuper=0x6f,
        invokeDirect=0x70,
        invokeStatic=0x71,
        invokeInterface=0x72,
        returnVNo=0x73,
        invokeVirtualR=0x74,
        invokeSuperR=0x75,
        invokeDirectR=0x76,
        invokeStaticR=0x77,
        invokeInterfaceR=0x78,

        //stub 79-7a unused
        //stub 7b-8f change-prim-type
        //stub 90-af 8 bit computation
        //stub b0-cf 4 bit computation
        //stub d0-d7 16 bit constant computation
        //stub d8-e2 8 bit constant computation
    };
    enum ArtOpCode {
        igetQ=0xe3,
        igetWQ=0xe4,
        igetObQ=0xe5,
        iputQ=0xe6,
        iputWQ=0xe7,
        iputObQ=0xe8,
        invokeVirtualQ=0xe9,
        invokeVirtualRQ=0xea,
        iputBooleanQ=0xeb,
        iputByteQ=0xec,
        iputCharQ=0xed,
        iputShortQ=0xee,
        igetBooleanQ=0xef,
        igetByteQ=0xf0,
        igetCharQ=0xf1,
        igetShortQ=0xf2,
        invokeLambda=0xf3,
        //unused 0xf4
        captureVariable=0xf5,
        createLambda=0xf6,
        liberateVariable =0xf7,
        boxLambda=0xf8,
        unboxLambda=0xf9,
    };
    enum DalvikOpCode {
        OP_IGET_VOLATILE = 0xe3,
        OP_IPUT_VOLATILE = 0xe4,
        OP_SGET_VOLATILE = 0xe5,
        OP_SPUT_VOLATILE = 0xe6,
        OP_IGET_OBJECT_VOLATILE = 0xe7,
        OP_IGET_WIDE_VOLATILE = 0xe8,
        OP_IPUT_WIDE_VOLATILE = 0xe9,
        OP_SGET_WIDE_VOLATILE = 0xea,
        OP_SPUT_WIDE_VOLATILE = 0xeb,
        OP_BREAKPOINT = 0xec,
        OP_THROW_VERIFICATION_ERROR = 0xed,
        OP_EXECUTE_INLINE = 0xee,
        OP_EXECUTE_INLINE_RANGE = 0xef,
        OP_INVOKE_OBJECT_INIT_RANGE = 0xf0,
        OP_RETURN_VOID_BARRIER = 0xf1,
        OP_IGET_QUICK = 0xf2,
        OP_IGET_WIDE_QUICK = 0xf3,
        OP_IGET_OBJECT_QUICK = 0xf4,
        OP_IPUT_QUICK = 0xf5,
        OP_IPUT_WIDE_QUICK = 0xf6,
        OP_IPUT_OBJECT_QUICK = 0xf7,
        OP_INVOKE_VIRTUAL_QUICK = 0xf8,
        OP_INVOKE_VIRTUAL_QUICK_RANGE = 0xf9,
        OP_INVOKE_SUPER_QUICK = 0xfa,
        OP_INVOKE_SUPER_QUICK_RANGE = 0xfb,
        OP_IPUT_OBJECT_VOLATILE = 0xfc,
        OP_SGET_OBJECT_VOLATILE = 0xfd,
        OP_SPUT_OBJECT_VOLATILE = 0xfe,
    };


    class JumpNode {
    public:
        u4 ins_pos;
        u4* registerTypes;//char* is better?
        JumpNode *nextNode = nullptr;
        JumpNode(u4 ins_pos, u4 *registerTypes, JumpNode *nextNode = nullptr) : nextNode(nextNode), ins_pos(
                ins_pos), registerTypes(registerTypes) {
        }
        ~JumpNode(){
            delete [] registerTypes;
        }
    };

    class Range{
        u4 start=0;
        Range()= delete;
        Range* copy(){
            return new Range(start,end,preRange);
        }
        Range(u4 start,u4 end,Range* preRange):start(start),end(end),preRange(preRange){}
    public:
        u4 end=UNDEFINED;
        Range* preRange= nullptr;
        explicit Range(u4 start,Range* preRange= nullptr):start(start),preRange(preRange){};
        static Range*  startNewRange(Range*&lastRange,Range*& nextRange, u4 end, u4 newStart){
            Range* range=nextRange== nullptr?lastRange:nextRange->preRange ;
            if(range->start > end){
                LOGW("Illegal range,end=%u less than start=%u", end, lastRange->start);
            }
            range->end=end;
            range=lastRange;
            do{
                if(newStart<=range->end&&newStart>=range->start){
                    return range;
                }
                if(newStart<range->start&&newStart>range->preRange->end){
                    Range* newRange=new Range(newStart,range->start-1,range->preRange);
                    range->preRange=newRange;
                    nextRange=range;

                    return nullptr;//insert range if new start go back;
                }
            }while ((range=range->preRange)!= nullptr);
            //Now new range must be higher than end;
            if(newStart<=end){
                LOGW("Unexpected:New Start=%u less than end=%u",newStart,end);
            }
            Range* newRange=new Range(newStart);
            newRange->preRange= lastRange;
            lastRange =newRange;
            nextRange= nullptr;
            return nullptr;
        };

        static bool checkRange(Range *lastRange, Range *nextRange, u4 newStart, u4 lastPos) {
            Range *range = nextRange == nullptr ? lastRange : nextRange->preRange;
            u4 *rEndPtr = &range->end;
            u4 endValue = range->end;
            *rEndPtr = lastPos;
            do {
                if(newStart<=range->end&&newStart>=range->start){
                    *rEndPtr = endValue;
                    return false;
                }
            } while ((range = range->preRange) != nullptr);
            *rEndPtr = endValue;
            return true;
        }
        static void checkNextRange(u4 pos, Range *&nextRange, Range *lastRange){
            if(nextRange== nullptr) return ;
            if(nextRange->preRange== nullptr){
                LOGE("Next Range->preRange Meet Empty");
                lastRange->printRange();
                return;
            }
            if(nextRange->preRange->end!=nextRange->start-1){
                throw std::runtime_error(
                        formMessage("Not concatated range!,curEnd=", nextRange->preRange->end,
                                    ",newStart=", (lastRange->printRange(), nextRange->start - 1)));
            }
            if (pos>=nextRange->start){
                nextRange=seekNextRange(nextRange,lastRange);
                if(nextRange!= nullptr)
                    nextRange->preRange->end=nextRange->start-1;//should it just be ended?
            }

        }
        static Range* seekNextRange(Range* curRange,Range* lastRange){
            if(curRange==lastRange) return nullptr;
            Range* range;
            while ((range=lastRange->preRange)!=curRange){
                lastRange=range;
                if(range== nullptr){
                    LOGE("Unexpected range");
                    lastRange->printRange();
                    curRange->printRange();
                    break;
                }
            }
            return lastRange;
        }
        ~Range(){
            delete preRange;
        }
        void printRange(){
            Range* range=this;
            do{
                LOGE("Range from %u to %u",range->start,range->end);
            }while ((range=range->preRange)!= nullptr);
        }
    };

    struct Handler{
        u4 typeIdx;
        u4 offset;
    };

    struct TryItem{
        u4 pos;
        u4 handlerSize;
        Handler* handlers= nullptr;
        ~TryItem(){delete [] handlers;}
    };
    class TryMap{
        bool isMapped;
        u4 start;
        u4 end;
        u4 div=0;
        int size;
        TryItem* tries= nullptr;
        TryItem** tryMap= nullptr;
        static int tryItemCompare(const void* f,const void* s){
            TryItem* fir=(TryItem*)f;
            TryItem* sec=(TryItem*) s;
            return fir->pos-sec->pos;
        }
    public:
        TryMap(TryItem* tries,int size):tries(tries),size(size){
            qsort(tries, (size_t) size, sizeof(TryItem), tryItemCompare);
            start=tries[0].pos;
            end=tries[size-1].pos;
            if(size<=4) isMapped= false;
            else{
                //LOGV("Tries mapped start=%u,end=%u,size=%u",start,end,size);
                isMapped = true;
                div = end - start;
                u4 tmpDiv;
                for (int i = 0; i < size - 1; ++i) {
                    tmpDiv=tries[i+1].pos-tries[i].pos;
                    if (tmpDiv < div) div = tmpDiv;
                }
                int len = 1 + (end - start) / div;
                typedef TryItem* tryPtr;
                tryMap=new tryPtr[len];
                memset(tryMap, 0, sizeof(tryPtr) * len);
                for(int i=0;i<size;++i){
                    u4 pos = (tries[i].pos - start) / div;
                    if (pos >= len || tryMap[pos] != nullptr) {
                        if (pos >= len)
                            LOGE("pos %u > len %d", pos, len);
                        else
                            LOGE("Abort try serials now try pos=%u, to be"
                                         " replace by try %d at pos=%u", tryMap[pos]->pos, i, pos);
                        for (int j = 0; j < size; ++j) {
                            LOGV("Try %d at pos=%u", j, tries[j].pos);
                        }
                        abort();
                    }
                    tryMap[pos] = &tries[i];
                }
            }
        }
        TryItem * seekTry(u4 pos);
        ~TryMap(){
            delete [] tries;
            delete [] tryMap;
        }
    };
    TryMap* tryMap= nullptr;
    const art::DexFile::TypeList* protoList;
    const art::DexFile::MethodId* methodId;
    const art::DexFile::CodeItem* codeItem;
    bool isInstance;
    CodeResolver(){}
    CodeResolver(const CodeResolver& copy)= delete;
    CodeResolver& operator=(CodeResolver&)= delete;

    u4 getVMethodFromIndex(u4 classIdx, u4 vIdx);

    u4 getFiledFromOffset(u4 classIdx, u4 fieldOffset);
    void initTries();
    void initRegisters(u4* registers);
    void checkRegRange(u4 index){
        if(index>=codeItem->registers_size_){
            LOGE("reg index out of range,index=%u,max=%u",index,codeItem->registers_size_);
            throw std::out_of_range("");
        }
    }
    static void threadInit();
    static void* runResolver(void* args);
    static void threadDestroy();

    static void handleExecuteInline(u2 insns[], u4 pos, u1 *ins);

    static void verifyRegCount(u2 insns[], u4 pos);
    static bool forkNode(const art::DexFile::CodeItem *code, JumpNode *curNode, Range *lastRAnge,
                         Range *nextRange, u4 lastPos, u4 newPos);

     void alterField(const JumpNode *curNode,
                     u2 *insns, u1 rOb, u4 pos);

    void changeIdx( u2 *insns, u4 pos, u4 Idx) const;
public:
    u4 fileOffset;

    CodeResolver(JNIEnv *env_, const art::DexFile::CodeItem *codeItem,
                 const art::DexFile::MethodId *methodId_, bool isInstance_) : methodId(methodId_),
                                                                              protoList(
                                                                                      reinterpret_cast<const
            art::DexFile::TypeList*>(dexGlobal.dexFile->proto_ids_[methodId_->proto_idx_].parameters_off_!=0?dexGlobal.dexFile->
                    begin_+dexGlobal.dexFile->proto_ids_[methodId_->proto_idx_].parameters_off_: nullptr)
    ), isInstance(isInstance_), codeItem(codeItem){}
    bool pend();

    ~CodeResolver(){
        delete tryMap;
    }

    static bool checkAndReplaceOpCodes(u2 *insns, u4 insns_size);
    static void resetInlineTable();

    static u4 binarySearchType(const char *typeName, const art::DexFile *dexFile);
};

#endif
#endif //HOOKMANAGER_CODERESOLVER_H
