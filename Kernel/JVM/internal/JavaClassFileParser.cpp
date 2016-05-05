#include "JavaClassFileParser.h"
#include <JVM/JavaClass.hpp>
#include <JVM/ConstantPoolType.h>
namespace JVM {
	static inline uint32_t get4(void*& p) {
		uint32_t result = *(reinterpret_cast<uint32_t*>(p));
		p += 4;
		return result;
	}
	static inline uint16_t get2(void*& p) {
		uint16_t result = *(reinterpret_cast<uint16_t*>(p));
		p += 2;
		return result;
	}
	bool JavaClassFileParser::parseInterfaces(uint16_t*& interfaces, void*& data, size_t numInterfaces) {
		if (interfaces == NULL)
			return false;
		for(int i = 0; i < numInterfaces; i++)
			interfaces[i] = get2(data);
	}
	bool JavaClassFileParser::parseConstantPool(cp_info**& pool, void*& data, size_t numConstants) {
		if(constant_pool == NULL)
			return false;
		//Why does it start @ i=1?
		for(int i=1; i<numConstants; i++) {
			pool[i] = reinterpret_cast<cp_info*>(data);
			
			uint8_t tag = pool[i]->tag;
			unsigned int size = getConstantSizeByType(tag);
			data+= size;
			//printf("Constant pool %d type %d\n",i,(u1)constant_pool[i]->tag);
			if(isWideCpType(tag) {
				pool[i + 1] = NULL;
				i++;
			}
		}

		return TRUE;
	}
	bool JavaClassFileParser::parseFields(JavaField*& fields, void*& data, size_t numFields) {
		if (fields == NULL)
			return false;
		for(int i = 0; i < numFields; i++) {
			fields[i].modifiers = get2(data);
			fields[i].name_index = get2(data);
			fields[i].descriptor_index = get2(data);
			fields[i].attributes_count = get2(data);

			if(fields[i].attributes_count>0) {
				//skip attributes - we do not need in simple cases
				for(int a=0; a<fields[i].attributes_count; a++) {
					uint16_t name_index = get2(data);
					//printf("Attribute name index = %d\n", name_index);
					uint32_t len = get4(data);
					data+= len;
				}
			}
		}
		return true;
	}
	bool JavaClassFileParser::parseMethods(method_info_ref*& methods, void*& data, size_t numMethods) {
		if (methods == NULL)
			return false;
		
		for(int i = 0; i < numMethods; i++) {
			methods[i]->base = reinterpret_cast<method_info*>(data);
			method_info& method = methods[i];
			method.modifiers = get2(data);
			method.name_index = get2(data);
			method.descriptor_index = get2(data);
			method.attributes_count = get2(data);
			
			//CString strName, strDesc;
			//GetStringFromConstPool(methods[i].name_index, strName);
			//GetStringFromConstPool(methods[i].descriptor_index, strDesc);

			//wprintf(_T("Method = %s%s\n"),strName, strDesc);
			
			//printf("Method has total %d attributes\n",methods[i].attributes_count);
			if(method->attributes_count > 0) {
				method.code = new Code_attribute;
				//skip attributes
				for(int a = 0; a < method->attributes_count; a++) {
					uint16_t name_index = get2(p);
					String* name = lookupAttr(name_index);//TODO fix
					
					//TODO is there a better way to do this? (maybe compare the indecies?)
					if (name->equalsIgnoreCase("Code", 4)) {
						//TODO finish porting
						char* ca = reinterpret_cast<char*>(p);
						pCode_attr->attribute_name_index=name_index;//already scanned;
						pCode_attr->attribute_length=get4(ca);
						pCode_attr->max_stack=get2(ca);
						pCode_attr->max_locals=get2(ca);
						pCode_attr->code_length=get4(ca);
						if(pCode_attr->code_length>0) {
							pCode_attr->code = new u1[pCode_attr->code_length];
							memcpy(pCode_attr->code,ca, pCode_attr->code_length);

							/*
							printf("\nCODE\n");
							for(u4 i=0;i<pCode_attr->code_length;i++)
								printf("%d ", pCode_attr->code[i]);
							printf("\nENDCODE\n");
							*/

						} else {
							// may be native code ??
							method->codeRef->code=NULL;
						}
						ca+=pCode_attr->code_length;
						pCode_attr->exception_table_length = getu2(ca);ca+=2;

						if(pCode_attr->exception_table_length > 0) {
							pCode_attr->exception_table = new Exception_table[pCode_attr->exception_table_length];
							for(int ext= 0; ext<pCode_attr->exception_table_length; ext++) {
								pCode_attr->exception_table[ext].start_pc = getu2(ca); ca+=2;
								pCode_attr->exception_table[ext].end_pc = getu2(ca); ca+=2;
								pCode_attr->exception_table[ext].handler_pc = getu2(ca); ca+=2;
								pCode_attr->exception_table[ext].catch_type = getu2(ca); ca+=2;
							}
						}
					}
					//printf("Attribute name index = %d\n", name_index);
					uint32_t len = get4(p);
					p+= len;
				}
			}		
		}
	}
	bool JavaClassFileParser::parseClass(JavaClassFile*& clazz, void*& data, size_t len) {
		if (data == NULL || len < sizeof(JavaClassFile) + 20)
			return false;
		void* p = data;
		if ((file.magic = get4(p)) != 0xCAFEBABE)
			return false;
		clazz->minor = get2(p);
		clazz->major = get2(p);
		
		if ((clazz->constantPoolSize = get2(p)) > 0) {
			clazz->constantPool = new cp_info*[clazz->constantPoolSize - 1];
			parseConstantPool(clazz->constantPool, p, clazz->constantPoolSize);
		} else {
			clazz->constantPool = NULL;
		}
		
		clazz->modifiers = get2(p);
		clazz->this_class = get2(p);
		clazz->super_class = get2(p);
		
		if ((clazz->numInterfaces = get2(p)) > 0) {
			clazz->interfaces = new uint16_t[clazz->numInterfaces];
			parseInterfaces(clazz->interfaces, p, clazz->numInterfaces);
		} else {
			clazz->interfaces = NULL;
		}
		
		if ((clazz->numFields = get2(p)) > 0) {
			clazz->fields = new JavaField*[clazz->numFields];
			parseFields(clazz->fields, p, clazz->numFields);
		} else {
			clazz->fields = NULL;
		}
		
		//parse methods
		if ((clazz->numMethods = get2(p)) > 0) {
			clazz->methods = new method_info[clazz->numMethods];
			parseMethods(clazz->methods, p, clazz->numMethods);
		} else {
			clazz->methods = NULL;
		}
		
		if ((clazz->numAttributes = get2(p)) > 0) {
			clazz->attributes = new attribute_info[clazz->numAttributes];
			parseAttributes(clazz->attributes, p, clazz->numAttributes);
		} else {
			clazz->attributes = NULL;
		}
		return true;
	}
	
}