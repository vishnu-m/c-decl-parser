#include <clang-c/Index.h>
#include <stdio.h>

enum CXChildVisitResult visitor(CXCursor, CXCursor, CXClientData); 
enum CXChildVisitResult enum_child_visitor(CXCursor, CXCursor, CXClientData); 
enum CXChildVisitResult struct_child_visitor(CXCursor, CXCursor, CXClientData); 

void enum_handler(CXCursor, CXCursor, CXClientData);
void struct_handler(CXCursor, CXCursor, CXClientData);
void union_handler(CXCursor, CXCursor, CXClientData);

void print_CXString(CXString s)
{
        printf("%s", clang_getCString(s));
        clang_disposeString(s);
}

void print_cursor_type(CXCursor cursor)
{
        CXType cursor_type = clang_getCursorType(cursor);
        print_CXString(clang_getTypeSpelling(cursor_type));
}

void print_cursor_spelling(CXCursor cursor) 
{
        CXString cursor_spelling = clang_getCursorSpelling(cursor);
        print_CXString(cursor_spelling);
}

void print_parent(CXCursor cursor) 
{
        CXCursor parent = clang_getCursorLexicalParent(cursor);
        print_CXString(clang_getCursorDisplayName(parent));
}

void print_storage_specifier(CXCursor cursor){
        enum CX_StorageClass sc_specifier = clang_Cursor_getStorageClass(cursor);
        
        switch(sc_specifier) {
                case CX_SC_Extern:
                        printf("extern");
                        break;
                
                case CX_SC_Static:
                        printf("static");
                        break;
                
                case CX_SC_Auto:
                        printf("auto"); 
                        break;

                case CX_SC_Register:
                        printf("register");
                        break;
        }
}

void enum_handler(CXCursor cursor, CXCursor parent, CXClientData client_data) 
{
        printf("EnumDecl\t\"");
        print_cursor_spelling(cursor);
        printf("\"\t\tParent = \"");
        print_cursor_spelling(parent);
        printf("\"\n");
        clang_visitChildren(cursor, enum_child_visitor, 0);
}

void struct_handler(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
        printf("StructDecl\t\"");
        print_cursor_spelling(cursor);
        printf("\"\t\tParent = \"");
        print_cursor_spelling(parent);
        printf("\"\n");
        clang_visitChildren(cursor, struct_child_visitor, 0);
}

void union_handler(CXCursor cursor, CXCursor parent, CXClientData client_data) 
{
        printf("UnionDecl\t\"");
        print_cursor_spelling(cursor);
        printf("\"\t\tParent = \"");
        print_cursor_spelling(parent);
        printf("\"\n");
        clang_visitChildren(cursor, struct_child_visitor, 0);
}

void function_handler(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
        CXType type = clang_getCursorType(cursor);
        int num_args = clang_Cursor_getNumArguments(cursor);
        CINDEX_LINKAGE unsigned is_function_inline;
        is_function_inline = clang_Cursor_isFunctionInlined(cursor);
        
        printf("FunctionDecl\t");
        if (is_function_inline) {
                printf("\t\t inline \t\t");
        }
        printf("\"");
        print_cursor_spelling(cursor);
        printf("\"\t\tstorage class specifier = \"");
        print_storage_specifier(cursor);
        printf("\"");
        printf("\t\treturn type = \"");
        print_CXString(clang_getTypeSpelling(clang_getResultType(type)));
        printf("\"");
        printf("\tArgs = \n");

        for (int i = 0; i < num_args; ++i) {
                CXCursor arg_cursor = clang_Cursor_getArgument(cursor, i);
                CXString arg_name = clang_getCursorSpelling(arg_cursor);
                CXType arg_data_type = clang_getArgType(type, i);
                printf("\t\t\"");
                print_CXString(arg_name);
                printf("\"");
                printf("\t\ttype=\"");
                print_CXString(clang_getTypeSpelling(arg_data_type));
                printf("\"\n");
        }
}

enum CXChildVisitResult enum_child_visitor(CXCursor cursor, CXCursor parent, CXClientData client_data)  
{
        enum CXCursorKind cursor_kind = clang_getCursorKind(cursor);

        switch(cursor_kind) {
                case CXCursor_IntegerLiteral: {
                        long long enum_const_value = clang_getEnumConstantDeclValue(parent);
                        printf("IntegerLiteral\t\t value = \"%lld\" \t\tParent = \"", enum_const_value);
                        print_cursor_spelling(parent);
                        printf("\"\n");
                        break;
                }

                case CXCursor_EnumConstantDecl:
                        printf("EnumConstantDecl\t\"");
                        print_cursor_spelling(cursor);
                        printf("\"\t\tParent = \"");
                        print_cursor_spelling(parent);
                        printf("\"\n");
                        break;

                default:
                        printf("Unaddressed - ");
                        print_CXString(clang_getCursorKindSpelling(cursor_kind));
                        printf("\n");
        }
        return CXChildVisit_Recurse;
}

enum CXChildVisitResult struct_child_visitor(CXCursor cursor, CXCursor parent, CXClientData client_data)
{
        enum CXCursorKind cursor_kind = clang_getCursorKind(cursor); 

        switch(cursor_kind) {
                case CXCursor_FieldDecl:
                        printf("FieldDecl\t\"");
                        print_cursor_spelling(cursor);
                        printf("\"\t\ttype = \"");
                        print_cursor_type(cursor);
                        printf("\"");
                        int is_bit_field = clang_Cursor_isBitField(cursor);
                        
                        if (is_bit_field) {
                                printf("\t\t(bitfield = %d)", clang_getFieldDeclBitWidth(cursor));
                        }

                        printf("\t\tParent = \"");
                        print_cursor_spelling(parent);
                        printf("\"\n");
                        break;

                case CXCursor_StructDecl:
                        struct_handler(cursor, parent, 0);
                        break;

                case CXCursor_EnumDecl:
                        enum_handler(cursor, parent, 0);
                        break;

                case CXCursor_UnionDecl:
                        union_handler(cursor, parent, 0);
                        break;

                default:
                        printf("Unaddressed - ");
                        print_CXString(clang_getCursorKindSpelling(cursor_kind));
                        printf("\n");  
        }
        return CXChildVisit_Continue;
}

enum CXChildVisitResult toplevel_visitor(CXCursor cursor, CXCursor parent, CXClientData client_data) 
{
        enum CXCursorKind cursor_kind = clang_getCursorKind(cursor); 

        switch(cursor_kind) {
                case CXCursor_EnumDecl:
                        enum_handler(cursor, parent, 0);
                        break;

                case CXCursor_StructDecl:
                        struct_handler(cursor, parent, 0);
                        break;

                case CXCursor_UnionDecl:
                        union_handler(cursor, parent, 0);
                        break;

                case CXCursor_TypedefDecl:
                        printf("TypedefDecl\t\t");
                        printf("underlying type = \"");
                        print_CXString(clang_getTypeSpelling(clang_getTypedefDeclUnderlyingType(cursor)));
                        printf("\"\t\ttype = \"");
                        print_cursor_type(cursor);
                        printf("\"\n");
                        break;

                case CXCursor_FunctionDecl:
                        function_handler(cursor, parent, 0);
                        break;

                case CXCursor_VarDecl:
                        printf("VarDecl\t\t\"");
                        print_cursor_spelling(cursor);
                        printf("\"\t\tstorage class specifier = \"");
                        print_storage_specifier(cursor);
                        printf("\"");
                        printf("\t\ttype = \"");
                        print_cursor_type(cursor);
                        printf("\"\n");
                        break;
                        
                default:
                        printf("Unaddressed - ");
                        print_CXString(clang_getCursorKindSpelling(cursor_kind));
                        printf("\n");
        }
        return CXChildVisit_Continue;
}

int main(int argc, char **argv) 
{
        CXIndex index = clang_createIndex(1, 0);
        CXTranslationUnit TU = clang_parseTranslationUnit(index, 0, argv, argc, 0, 0, CXTranslationUnit_None);
        CXCursor cursor = clang_getTranslationUnitCursor(TU);
        clang_visitChildren(cursor, toplevel_visitor, 0);
        clang_disposeTranslationUnit(TU);
        clang_disposeIndex(index);
        return 0;
}