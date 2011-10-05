#include "libarchive_internal.h"

VALUE rb_mArchive;
VALUE rb_eArchiveError;

/* */
VALUE rb_libarchive_s_version_number(VALUE self) {
#if ARCHIVE_VERSION >= 2005000
  return INT2NUM(archive_version_number());
#else
  return INT2NUM(archive_version_stamp());
#endif
}

/* */
VALUE rb_libarchive_s_version_string(VALUE self) {
#if ARCHIVE_VERSION_NUMBER >= 2005000
  return rb_str_new2(archive_version_string());
#else
  return rb_str_new2(archive_version());
#endif
}

void DLLEXPORT Init_libarchive_ruby() {
  rb_mArchive = rb_define_module("Archive");
  rb_define_const(rb_mArchive, "VERSION", rb_str_new2(VERSION));

  rb_define_const(rb_mArchive, "COMPRESSION_NONE",     INT2NUM(ARCHIVE_COMPRESSION_NONE));
  rb_define_const(rb_mArchive, "COMPRESSION_GZIP",     INT2NUM(ARCHIVE_COMPRESSION_GZIP));
  rb_define_const(rb_mArchive, "COMPRESSION_BZIP2",    INT2NUM(ARCHIVE_COMPRESSION_BZIP2));
  rb_define_const(rb_mArchive, "COMPRESSION_COMPRESS", INT2NUM(ARCHIVE_COMPRESSION_COMPRESS));
  // XXX:
  /*
  rb_define_const(rb_mArchive, "COMPRESSION_PROGRAM",  INT2NUM(ARCHIVE_COMPRESSION_PROGRAM));
  rb_define_const(rb_mArchive, "COMPRESSION_LZMA",     INT2NUM(ARCHIVE_COMPRESSION_LZMA));
  */

  rb_define_const(rb_mArchive, "FORMAT_BASE_MASK",           INT2NUM(ARCHIVE_FORMAT_BASE_MASK));
  rb_define_const(rb_mArchive, "FORMAT_CPIO",                INT2NUM(ARCHIVE_FORMAT_CPIO));
  rb_define_const(rb_mArchive, "FORMAT_CPIO_POSIX",          INT2NUM(ARCHIVE_FORMAT_CPIO_POSIX));
  rb_define_const(rb_mArchive, "FORMAT_CPIO_BIN_LE",         INT2NUM(ARCHIVE_FORMAT_CPIO_BIN_LE));
  rb_define_const(rb_mArchive, "FORMAT_CPIO_BIN_BE",         INT2NUM(ARCHIVE_FORMAT_CPIO_BIN_BE));
  rb_define_const(rb_mArchive, "FORMAT_CPIO_SVR4_NOCRC",     INT2NUM(ARCHIVE_FORMAT_CPIO_SVR4_NOCRC));
  rb_define_const(rb_mArchive, "FORMAT_CPIO_SVR4_CRC",       INT2NUM(ARCHIVE_FORMAT_CPIO_SVR4_CRC));
  rb_define_const(rb_mArchive, "FORMAT_SHAR",                INT2NUM(ARCHIVE_FORMAT_SHAR));
  rb_define_const(rb_mArchive, "FORMAT_SHAR_BASE",           INT2NUM(ARCHIVE_FORMAT_SHAR_BASE));
  rb_define_const(rb_mArchive, "FORMAT_SHAR_DUMP",           INT2NUM(ARCHIVE_FORMAT_SHAR_DUMP));
  rb_define_const(rb_mArchive, "FORMAT_TAR",                 INT2NUM(ARCHIVE_FORMAT_TAR));
  rb_define_const(rb_mArchive, "FORMAT_TAR_USTAR",           INT2NUM(ARCHIVE_FORMAT_TAR_USTAR));
  rb_define_const(rb_mArchive, "FORMAT_TAR_PAX_INTERCHANGE", INT2NUM(ARCHIVE_FORMAT_TAR_PAX_INTERCHANGE));
  rb_define_const(rb_mArchive, "FORMAT_TAR_PAX_RESTRICTED",  INT2NUM(ARCHIVE_FORMAT_TAR_PAX_RESTRICTED));
  rb_define_const(rb_mArchive, "FORMAT_TAR_GNUTAR",          INT2NUM(ARCHIVE_FORMAT_TAR_GNUTAR));
  rb_define_const(rb_mArchive, "FORMAT_ISO9660",             INT2NUM(ARCHIVE_FORMAT_ISO9660));
  rb_define_const(rb_mArchive, "FORMAT_ISO9660_ROCKRIDGE",   INT2NUM(ARCHIVE_FORMAT_ISO9660_ROCKRIDGE));
  rb_define_const(rb_mArchive, "FORMAT_ZIP",                 INT2NUM(ARCHIVE_FORMAT_ZIP));
  rb_define_const(rb_mArchive, "FORMAT_EMPTY",               INT2NUM(ARCHIVE_FORMAT_EMPTY));
  rb_define_const(rb_mArchive, "FORMAT_AR",                  INT2NUM(ARCHIVE_FORMAT_AR));
  rb_define_const(rb_mArchive, "FORMAT_AR_GNU",              INT2NUM(ARCHIVE_FORMAT_AR_GNU));
  rb_define_const(rb_mArchive, "FORMAT_AR_BSD",              INT2NUM(ARCHIVE_FORMAT_AR_BSD));
#ifdef ARCHIVE_FORMAT_MTREE
  rb_define_const(rb_mArchive, "FORMAT_MTREE",               INT2NUM(ARCHIVE_FORMAT_MTREE));
#endif

  rb_define_const(rb_mArchive, "EXTRACT_OWNER",              INT2NUM(ARCHIVE_EXTRACT_OWNER));
  rb_define_const(rb_mArchive, "EXTRACT_PERM",               INT2NUM(ARCHIVE_EXTRACT_PERM));
  rb_define_const(rb_mArchive, "EXTRACT_TIME",               INT2NUM(ARCHIVE_EXTRACT_TIME));
  rb_define_const(rb_mArchive, "EXTRACT_NO_OVERWRITE",       INT2NUM(ARCHIVE_EXTRACT_NO_OVERWRITE));
  rb_define_const(rb_mArchive, "EXTRACT_UNLINK",             INT2NUM(ARCHIVE_EXTRACT_UNLINK));
  rb_define_const(rb_mArchive, "EXTRACT_ACL",                INT2NUM(ARCHIVE_EXTRACT_ACL));
  rb_define_const(rb_mArchive, "EXTRACT_FFLAGS",             INT2NUM(ARCHIVE_EXTRACT_FFLAGS));
  rb_define_const(rb_mArchive, "EXTRACT_XATTR",              INT2NUM(ARCHIVE_EXTRACT_XATTR));
  rb_define_const(rb_mArchive, "EXTRACT_SECURE_SYMLINKS",    INT2NUM(ARCHIVE_EXTRACT_SECURE_SYMLINKS));
  rb_define_const(rb_mArchive, "EXTRACT_SECURE_NODOTDOT",    INT2NUM(ARCHIVE_EXTRACT_SECURE_NODOTDOT));
  rb_define_const(rb_mArchive, "EXTRACT_NO_AUTODIR",         INT2NUM(ARCHIVE_EXTRACT_NO_AUTODIR));
  rb_define_const(rb_mArchive, "EXTRACT_NO_OVERWRITE_NEWER", INT2NUM(ARCHIVE_EXTRACT_NO_OVERWRITE_NEWER));
#ifdef ARCHIVE_EXTRACT_SPARSE
  rb_define_const(rb_mArchive, "EXTRACT_SPARSE",             INT2NUM(ARCHIVE_EXTRACT_SPARSE));
#endif

  rb_define_module_function(rb_mArchive, "version_number", rb_libarchive_s_version_number, 0);
  rb_define_module_function(rb_mArchive, "version_string", rb_libarchive_s_version_string, 0);

  rb_eArchiveError = rb_define_class_under(rb_mArchive, "Error", rb_eStandardError);

  Init_libarchive_reader();
  Init_libarchive_writer();
  Init_libarchive_archive();
  Init_libarchive_entry();
}
#include "libarchive_internal.h"

extern VALUE rb_cArchiveReader;
extern VALUE rb_cArchiveWriter;
extern VALUE rb_eArchiveError;

static void rb_libarchive_archive_free(struct rb_libarchive_archive_container *p) {
  xfree(p);
}

static void rb_libarchive_archive_mark(struct rb_libarchive_archive_container *p) {
  rb_gc_mark(p->memory);
}

VALUE rb_libarchive_archive_alloc(VALUE klass) {
  struct rb_libarchive_archive_container *p = ALLOC(struct rb_libarchive_archive_container);
  p->ar = NULL;
  p->eof = 0;
  p->memory = Qnil;
  return Data_Wrap_Struct(klass, rb_libarchive_archive_mark, rb_libarchive_archive_free, p);
}

/* */
static VALUE rb_libarchive_archive_position_compressed(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  return LL2NUM(archive_position_compressed(p->ar));
}

/* */
static VALUE rb_libarchive_archive_position_uncompressed(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  return LL2NUM(archive_position_uncompressed(p->ar));
}

/* */
static VALUE rb_libarchive_archive_compression_name(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  return rb_str_new2(archive_compression_name(p->ar));
}

/* */
static VALUE rb_libarchive_archive_compression(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  return INT2NUM(archive_compression(p->ar));
}

/* */
static VALUE rb_libarchive_archive_format_name(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  return rb_str_new2(archive_format_name(p->ar));
}

/* */
static VALUE rb_libarchive_archive_format(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  return NUM2INT(archive_format(p->ar));
}

void Init_libarchive_archive() {
  rb_define_method(rb_cArchiveReader, "position_compressed", rb_libarchive_archive_position_compressed, 0);
  rb_define_method(rb_cArchiveWriter, "position_compressed", rb_libarchive_archive_position_compressed, 0);
  rb_define_method(rb_cArchiveReader, "position_uncompressed", rb_libarchive_archive_position_uncompressed, 0);
  rb_define_method(rb_cArchiveWriter, "position_uncompressed", rb_libarchive_archive_position_uncompressed, 0);
  rb_define_method(rb_cArchiveReader, "compression_name", rb_libarchive_archive_compression_name, 0);
  rb_define_method(rb_cArchiveWriter, "compression_name", rb_libarchive_archive_compression_name, 0);
  rb_define_method(rb_cArchiveReader, "compression", rb_libarchive_archive_compression, 0);
  rb_define_method(rb_cArchiveWriter, "compression", rb_libarchive_archive_compression, 0);
  rb_define_method(rb_cArchiveReader, "format_name", rb_libarchive_archive_format_name, 0);
  rb_define_method(rb_cArchiveWriter, "format_name", rb_libarchive_archive_format_name, 0);
  rb_define_method(rb_cArchiveReader, "format", rb_libarchive_archive_format, 0);
  rb_define_method(rb_cArchiveWriter, "format", rb_libarchive_archive_format, 0);
}
#include "libarchive_internal.h"

extern VALUE rb_mArchive;
VALUE rb_cArchiveEntry;
extern VALUE rb_eArchiveError;

static void rb_libarchive_entry_free(struct rb_libarchive_entry_container *p) {
  xfree(p);
}

static VALUE rb_libarchive_entry_alloc(VALUE klass) {
  struct rb_libarchive_entry_container *p = ALLOC(struct rb_libarchive_entry_container);
  p->ae = NULL;
  p->must_close = 1;
  return Data_Wrap_Struct(klass, 0, rb_libarchive_entry_free, p);
}

/* */
VALUE rb_libarchive_entry_close(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);

  if (!p->must_close) {
    rb_raise(rb_eArchiveError, "Close entry failed: It is not necessary to close");
  }

  archive_entry_free(p->ae);
  p->ae = NULL;
  return Qnil;
}

VALUE rb_libarchive_entry_new(struct archive_entry *ae, int must_close) {
  VALUE entry;
  struct rb_libarchive_entry_container *p;
  entry = rb_funcall(rb_cArchiveEntry, rb_intern("new"), 0);
  Data_Get_Struct(entry, struct rb_libarchive_entry_container, p);
  p->ae = ae;
  p->must_close = must_close;
  return entry;
}

/* */
static VALUE rb_libarchive_entry_atime(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2TIME((long) archive_entry_atime(p->ae));
}

/* */
static VALUE rb_libarchive_entry_atime_nsec(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_atime_nsec(p->ae));
}

/* */
static VALUE rb_libarchive_entry_atime_is_set(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return archive_entry_atime_is_set(p->ae) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_birthtime(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2TIME((long) archive_entry_birthtime(p->ae));
}

/* */
static VALUE rb_libarchive_entry_birthtime_nsec(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_birthtime_nsec(p->ae));
}

/* */
static VALUE rb_libarchive_entry_birthtime_is_set(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return archive_entry_birthtime_is_set(p->ae) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_ctime(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2TIME((long) archive_entry_ctime(p->ae));
}

/* */
static VALUE rb_libarchive_entry_ctime_nsec(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_ctime_nsec(p->ae));
}

/* */
static VALUE rb_libarchive_entry_ctime_is_set(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return archive_entry_ctime_is_set(p->ae) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_dev(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_dev(p->ae));
}

/* */
static VALUE rb_libarchive_entry_devmajor(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_devmajor(p->ae));
}

/* */
static VALUE rb_libarchive_entry_devminor(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_devminor(p->ae));
}

/* */
static VALUE rb_libarchive_entry_filetype(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return INT2NUM(archive_entry_filetype(p->ae));
}

/* */
static VALUE rb_libarchive_entry_is_directory(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return S_ISDIR(archive_entry_filetype(p->ae)) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_is_character_special(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return S_ISCHR(archive_entry_filetype(p->ae)) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_is_block_special(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return S_ISBLK(archive_entry_filetype(p->ae)) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_is_regular(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return S_ISREG(archive_entry_filetype(p->ae)) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_is_symbolic_link(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return S_ISLNK(archive_entry_filetype(p->ae)) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_is_socket(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return S_ISSOCK(archive_entry_filetype(p->ae)) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_is_fifo(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return S_ISFIFO(archive_entry_filetype(p->ae)) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_fflags(VALUE self) {
  struct rb_libarchive_entry_container *p;
  long set, clear;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  archive_entry_fflags(p->ae, &set, &clear);
  return rb_ary_new3(2, LONG2NUM(set), LONG2NUM(clear));
}

/* */
static VALUE rb_libarchive_entry_fflags_text(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *fflags_text;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  fflags_text = archive_entry_fflags_text(p->ae);
  return (fflags_text != NULL) ? rb_str_new2(fflags_text) : Qnil;
}

/* */
static VALUE rb_libarchive_entry_gid(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_gid(p->ae));
}

/* */
static VALUE rb_libarchive_entry_gname(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *gname;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  gname = archive_entry_gname(p->ae);
  return (gname != NULL) ? rb_str_new2(gname) : Qnil;
}

/* */
static VALUE rb_libarchive_entry_hardlink(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *hardlink;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  hardlink = archive_entry_hardlink(p->ae);
  return (hardlink != NULL) ? rb_str_new2(hardlink) : Qnil;
}

/* */
static VALUE rb_libarchive_entry_ino(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  return LONG2NUM(archive_entry_ino(p->ae));
}

/* */
static VALUE rb_libarchive_entry_mode(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  return LONG2NUM(archive_entry_mode(p->ae));
}

/* */
static VALUE rb_libarchive_entry_mtime(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2TIME((long) archive_entry_mtime(p->ae));
}

/* */
static VALUE rb_libarchive_entry_mtime_nsec(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_mtime_nsec(p->ae));
}

/* */
static VALUE rb_libarchive_entry_mtime_is_set(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return archive_entry_mtime_is_set(p->ae) ? Qtrue : Qfalse;
}

/* */
static VALUE rb_libarchive_entry_nlink(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_nlink(p->ae));
}

/* */
static VALUE rb_libarchive_entry_pathname(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *pathname;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  pathname = archive_entry_pathname(p->ae);
  return (pathname != NULL) ? rb_str_new2(pathname) : Qnil;
}

/* */
static VALUE rb_libarchive_entry_rdev(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_rdev(p->ae));
}

/* */
static VALUE rb_libarchive_entry_rdevmajor(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_rdevmajor(p->ae));
}

/* */
static VALUE rb_libarchive_entry_rdevminor(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_rdevminor(p->ae));
}

#if ARCHIVE_VERSION_NUMBER >= 2005003
/* */
static VALUE rb_libarchive_entry_sourcepath(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *sourcepath;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  sourcepath = archive_entry_sourcepath(p->ae);
  return (sourcepath != NULL) ? rb_str_new2(sourcepath) : Qnil;
}
#endif

/* */
static VALUE rb_libarchive_entry_size(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LL2NUM(archive_entry_size(p->ae));
}

/* */
static VALUE rb_libarchive_entry_size_is_set(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return archive_entry_size_is_set(p->ae) ? Qtrue : Qfalse;
}

#if ARCHIVE_VERSION_NUMBER >= 2003002
/* */
static VALUE rb_libarchive_entry_strmode(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *strmode;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  strmode = archive_entry_strmode(p->ae);
  return (strmode != NULL) ? rb_str_new2(strmode) : Qnil;
}
#endif

/* */
static VALUE rb_libarchive_entry_symlink(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *symlink;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  symlink = archive_entry_symlink(p->ae);
  return (symlink != NULL) ? rb_str_new2(symlink) : Qnil;
}

/* */
static VALUE rb_libarchive_entry_uid(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return LONG2NUM(archive_entry_uid(p->ae));
}

/* */
static VALUE rb_libarchive_entry_uname(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *uname;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  uname = archive_entry_uname(p->ae);
  return (uname != NULL) ? rb_str_new2(uname) : Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_atime(VALUE self, VALUE v_time) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Class(v_time, rb_cTime);
  archive_entry_set_atime(p->ae, TIME2LONG(v_time), 0);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_atime2(VALUE self, VALUE v_time, VALUE v_ns) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Class(v_time, rb_cTime);
  Check_Type(v_ns, T_FIXNUM);
  archive_entry_set_atime(p->ae, TIME2LONG(v_time), NUM2LONG(v_ns));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_unset_atime(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  archive_entry_unset_atime(p->ae);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_birthtime(VALUE self, VALUE v_time) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Class(v_time, rb_cTime);
  archive_entry_set_birthtime(p->ae, TIME2LONG(v_time), 0);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_birthtime2(VALUE self, VALUE v_time, VALUE v_ns) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Class(v_time, rb_cTime);
  Check_Type(v_ns, T_FIXNUM);
  archive_entry_set_birthtime(p->ae, TIME2LONG(v_time), NUM2LONG(v_ns));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_unset_birthtime(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  archive_entry_unset_birthtime(p->ae);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_ctime(VALUE self, VALUE v_time) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Class(v_time, rb_cTime);
  archive_entry_set_ctime(p->ae, TIME2LONG(v_time), 0);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_ctime2(VALUE self, VALUE v_time, VALUE v_ns) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Class(v_time, rb_cTime);
  Check_Type(v_ns, T_FIXNUM);
  archive_entry_set_ctime(p->ae, TIME2LONG(v_time), NUM2LONG(v_ns));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_unset_ctime(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  archive_entry_unset_ctime(p->ae);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_dev(VALUE self, VALUE v_dev) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_dev, T_FIXNUM);
  archive_entry_set_dev(p->ae, NUM2LONG(v_dev));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_devmajor(VALUE self, VALUE v_dev) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_dev, T_FIXNUM);
  archive_entry_set_devmajor(p->ae, NUM2LONG(v_dev));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_devminor(VALUE self, VALUE v_dev) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_dev, T_FIXNUM);
  archive_entry_set_devminor(p->ae, NUM2LONG(v_dev));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_filetype(VALUE self, VALUE v_type) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_type, T_FIXNUM);
  archive_entry_set_filetype(p->ae, NUM2LONG(v_type));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_fflags(VALUE self, VALUE v_set, VALUE v_clear) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_set, T_FIXNUM);
  Check_Type(v_clear, T_FIXNUM);
  archive_entry_set_fflags(p->ae, (unsigned long) NUM2LONG(v_set), (unsigned long) NUM2LONG(v_clear));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_fflags_text(VALUE self, VALUE v_fflags_text) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_fflags_text, T_STRING);
  archive_entry_copy_fflags_text(p->ae, RSTRING_PTR(v_fflags_text));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_gid(VALUE self, VALUE v_gid) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_gid, T_FIXNUM);
  archive_entry_set_gid(p->ae, NUM2LONG(v_gid));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_gname(VALUE self, VALUE v_gname) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_gname, T_STRING);
  archive_entry_set_gname(p->ae, RSTRING_PTR(v_gname));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_gname(VALUE self, VALUE v_gname) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_gname, T_STRING);
  archive_entry_copy_gname(p->ae, RSTRING_PTR(v_gname));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_hardlink(VALUE self, VALUE v_hardlink) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_hardlink, T_STRING);
  archive_entry_set_hardlink(p->ae, RSTRING_PTR(v_hardlink));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_hardlink(VALUE self, VALUE v_hardlink) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_hardlink, T_STRING);
  archive_entry_copy_hardlink(p->ae, RSTRING_PTR(v_hardlink));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_ino(VALUE self, VALUE v_ino) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_ino, T_FIXNUM);
  archive_entry_set_ino(p->ae, (unsigned long) NUM2LONG(v_ino));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_link(VALUE self, VALUE v_link) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_link, T_STRING);
  archive_entry_set_link(p->ae, RSTRING_PTR(v_link));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_link(VALUE self, VALUE v_link) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_link, T_STRING);
  archive_entry_copy_link(p->ae, RSTRING_PTR(v_link));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_mode(VALUE self, VALUE v_mode) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_mode, T_STRING);
  archive_entry_set_mode(p->ae, NUM2INT(v_mode));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_mtime(VALUE self, VALUE v_time) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Class(v_time, rb_cTime);
  archive_entry_set_mtime(p->ae, TIME2LONG(v_time), 0);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_mtime2(VALUE self, VALUE v_time, VALUE v_ns) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Class(v_time, rb_cTime);
  Check_Type(v_ns, T_FIXNUM);
  archive_entry_set_mtime(p->ae, TIME2LONG(v_time), NUM2LONG(v_ns));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_unset_mtime(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  archive_entry_unset_mtime(p->ae);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_nlink(VALUE self, VALUE v_nlink) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_nlink, T_FIXNUM);
  archive_entry_set_nlink(p->ae, NUM2LONG(v_nlink));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_pathname(VALUE self, VALUE v_filename) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_filename, T_STRING);
  archive_entry_set_pathname(p->ae, RSTRING_PTR(v_filename));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_pathname(VALUE self, VALUE v_filename) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_filename, T_STRING);
  archive_entry_copy_pathname(p->ae, RSTRING_PTR(v_filename));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_perm(VALUE self, VALUE v_perm) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_perm, T_STRING);
  archive_entry_set_perm(p->ae, NUM2INT(v_perm));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_rdev(VALUE self, VALUE v_rdev) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_rdev, T_FIXNUM);
  archive_entry_set_rdev(p->ae, NUM2LONG(v_rdev));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_rdevmajor(VALUE self, VALUE v_rdev) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_rdev, T_FIXNUM);
  archive_entry_set_rdevmajor(p->ae, NUM2LONG(v_rdev));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_rdevminor(VALUE self, VALUE v_rdev) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_rdev, T_FIXNUM);
  archive_entry_set_rdevminor(p->ae, NUM2LONG(v_rdev));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_size(VALUE self, VALUE v_size) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_size, T_FIXNUM);
  archive_entry_set_size(p->ae, NUM2LL(v_size));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_unset_size(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  archive_entry_unset_size(p->ae);
  return Qnil;
}

#if ARCHIVE_VERSION_NUMBER >= 2005003
/* */
static VALUE rb_libarchive_entry_copy_sourcepath(VALUE self, VALUE v_sourcepath) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_sourcepath, T_STRING);
  archive_entry_copy_sourcepath(p->ae, RSTRING_PTR(v_sourcepath));
  return Qnil;
}
#endif

/* */
static VALUE rb_libarchive_entry_set_symlink(VALUE self, VALUE v_symlink) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_symlink, T_STRING);
  archive_entry_set_symlink(p->ae, RSTRING_PTR(v_symlink));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_symlink(VALUE self, VALUE v_symlink) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_symlink, T_STRING);
  archive_entry_copy_symlink(p->ae, RSTRING_PTR(v_symlink));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_uid(VALUE self, VALUE v_uid) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_uid, T_FIXNUM);
  archive_entry_set_uid(p->ae, NUM2LONG(v_uid));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_set_uname(VALUE self, VALUE v_uname) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_uname, T_STRING);
  archive_entry_set_uname(p->ae, RSTRING_PTR(v_uname));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_uname(VALUE self, VALUE v_uname) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_uname, T_STRING);
  archive_entry_copy_uname(p->ae, RSTRING_PTR(v_uname));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_stat(VALUE self, VALUE v_filename) {
  struct rb_libarchive_entry_container *p;
  const char *filename;
  struct stat s;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_filename, T_STRING);
  filename = RSTRING_PTR(v_filename);

  if (stat(filename, &s) != 0) {
    rb_raise(rb_eArchiveError, "Copy stat failed: %", strerror(errno));
  }

  archive_entry_copy_stat(p->ae, &s);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_copy_lstat(VALUE self, VALUE v_filename) {
  struct rb_libarchive_entry_container *p;
  const char *filename;
  struct stat s;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_filename, T_STRING);
  filename = RSTRING_PTR(v_filename);

  if (lstat(filename, &s) != 0) {
    rb_raise(rb_eArchiveError, "Copy stat failed: %", strerror(errno));
  }

  archive_entry_copy_stat(p->ae, &s);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_xattr_clear(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  archive_entry_xattr_clear(p->ae);
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_xattr_add_entry(VALUE self, VALUE v_name, VALUE v_value) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  Check_Type(v_name, T_STRING);
  Check_Type(v_value, T_STRING);
  archive_entry_xattr_add_entry(p->ae, RSTRING_PTR(v_name), RSTRING_PTR(v_value), RSTRING_LEN(v_value));
  return Qnil;
}

/* */
static VALUE rb_libarchive_entry_xattr_count(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return INT2NUM(archive_entry_xattr_count(p->ae));
}

/* */
static VALUE rb_libarchive_entry_xattr_reset(VALUE self) {
  struct rb_libarchive_entry_container *p;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);
  return INT2NUM(archive_entry_xattr_reset(p->ae));
}

/* */
static VALUE rb_libarchive_entry_xattr_next(VALUE self) {
  struct rb_libarchive_entry_container *p;
  const char *name;
  const void *value;
  size_t size;
  Data_Get_Struct(self, struct rb_libarchive_entry_container, p);
  Check_Entry(p);

  if (archive_entry_xattr_next(p->ae, &name, &value, &size) != ARCHIVE_OK) {
    return Qnil;
  } else {
    return rb_ary_new3(3, rb_str_new2(name), rb_str_new(value, size));
  }
}

void Init_libarchive_entry() {
  rb_cArchiveEntry = rb_define_class_under(rb_mArchive, "Entry", rb_cObject);
  rb_define_alloc_func(rb_cArchiveEntry, rb_libarchive_entry_alloc);
  rb_funcall(rb_cArchiveEntry, rb_intern("private_class_method"), 1, ID2SYM(rb_intern("new")));
  rb_define_method(rb_cArchiveEntry, "close", rb_libarchive_entry_close, 0);

  rb_define_method(rb_cArchiveEntry, "atime", rb_libarchive_entry_atime, 0);
  rb_define_method(rb_cArchiveEntry, "atime_nsec", rb_libarchive_entry_atime_nsec, 0);
  rb_define_method(rb_cArchiveEntry, "atime_is_set?", rb_libarchive_entry_atime_is_set, 0);
  rb_define_method(rb_cArchiveEntry, "birthtime", rb_libarchive_entry_birthtime, 0);
  rb_define_method(rb_cArchiveEntry, "birthtime_nsec", rb_libarchive_entry_birthtime_nsec, 0);
  rb_define_method(rb_cArchiveEntry, "birthtime_is_set?", rb_libarchive_entry_birthtime_is_set, 0);
  rb_define_method(rb_cArchiveEntry, "ctime", rb_libarchive_entry_ctime, 0);
  rb_define_method(rb_cArchiveEntry, "ctime_nsec", rb_libarchive_entry_ctime_nsec, 0);
  rb_define_method(rb_cArchiveEntry, "ctime_is_set?", rb_libarchive_entry_ctime_is_set, 0);
  rb_define_method(rb_cArchiveEntry, "dev", rb_libarchive_entry_dev, 0);
  rb_define_method(rb_cArchiveEntry, "devmajor", rb_libarchive_entry_devmajor, 0);
  rb_define_method(rb_cArchiveEntry, "devminor", rb_libarchive_entry_devminor, 0);
  rb_define_method(rb_cArchiveEntry, "filetype", rb_libarchive_entry_filetype, 0);
  rb_define_method(rb_cArchiveEntry, "directory?", rb_libarchive_entry_is_directory, 0);
  rb_define_method(rb_cArchiveEntry, "character_special?", rb_libarchive_entry_is_character_special, 0);
  rb_define_method(rb_cArchiveEntry, "block_special?", rb_libarchive_entry_is_block_special, 0);
  rb_define_method(rb_cArchiveEntry, "regular?", rb_libarchive_entry_is_regular, 0);
  rb_define_method(rb_cArchiveEntry, "symbolic_link?", rb_libarchive_entry_is_symbolic_link, 0);
  rb_define_method(rb_cArchiveEntry, "socket?", rb_libarchive_entry_is_socket, 0);
  rb_define_method(rb_cArchiveEntry, "fifo?", rb_libarchive_entry_is_fifo, 0);
  rb_define_method(rb_cArchiveEntry, "fflags", rb_libarchive_entry_fflags, 0);
  rb_define_method(rb_cArchiveEntry, "fflags_text", rb_libarchive_entry_fflags_text, 0);
  rb_define_method(rb_cArchiveEntry, "gid", rb_libarchive_entry_gid, 0);
  rb_define_method(rb_cArchiveEntry, "gname", rb_libarchive_entry_gname, 0);
  rb_define_method(rb_cArchiveEntry, "hardlink", rb_libarchive_entry_hardlink, 0);
  rb_define_method(rb_cArchiveEntry, "ino", rb_libarchive_entry_ino, 0);
  rb_define_method(rb_cArchiveEntry, "mode", rb_libarchive_entry_mode, 0);
  rb_define_method(rb_cArchiveEntry, "mtime", rb_libarchive_entry_mtime, 0);
  rb_define_method(rb_cArchiveEntry, "mtime_nsec", rb_libarchive_entry_mtime_nsec, 0);
  rb_define_method(rb_cArchiveEntry, "mtime_is_set?", rb_libarchive_entry_mtime_is_set, 0);
  rb_define_method(rb_cArchiveEntry, "nlink", rb_libarchive_entry_nlink, 0);
  rb_define_method(rb_cArchiveEntry, "pathname", rb_libarchive_entry_pathname, 0);
  rb_define_method(rb_cArchiveEntry, "rdev", rb_libarchive_entry_rdev, 0);
  rb_define_method(rb_cArchiveEntry, "rdevmajor", rb_libarchive_entry_rdevmajor, 0);
  rb_define_method(rb_cArchiveEntry, "rdevminor", rb_libarchive_entry_rdevminor, 0);
#if ARCHIVE_VERSION_NUMBER >= 2005003
  rb_define_method(rb_cArchiveEntry, "sourcepath", rb_libarchive_entry_sourcepath, 0);
#endif
  rb_define_method(rb_cArchiveEntry, "size", rb_libarchive_entry_size, 0);
  rb_define_method(rb_cArchiveEntry, "size_is_set?", rb_libarchive_entry_size_is_set, 0);
#if ARCHIVE_VERSION_NUMBER >= 2003002
  rb_define_method(rb_cArchiveEntry, "strmode", rb_libarchive_entry_strmode, 0);
#endif
  rb_define_method(rb_cArchiveEntry, "symlink", rb_libarchive_entry_symlink, 0);
  rb_define_method(rb_cArchiveEntry, "uid", rb_libarchive_entry_uid, 0);
  rb_define_method(rb_cArchiveEntry, "uname", rb_libarchive_entry_uname, 0);

  rb_define_method(rb_cArchiveEntry, "atime=", rb_libarchive_entry_set_atime, 1);
  rb_define_method(rb_cArchiveEntry, "set_atime", rb_libarchive_entry_set_atime2, 2);
  rb_define_method(rb_cArchiveEntry, "unset_atime", rb_libarchive_entry_unset_atime, 0);
  rb_define_method(rb_cArchiveEntry, "birthtimee=", rb_libarchive_entry_set_birthtime, 1);
  rb_define_method(rb_cArchiveEntry, "set_birthtime", rb_libarchive_entry_set_birthtime2, 2);
  rb_define_method(rb_cArchiveEntry, "unset_birthtime", rb_libarchive_entry_unset_birthtime, 0);
  rb_define_method(rb_cArchiveEntry, "ctime=", rb_libarchive_entry_set_ctime, 1);
  rb_define_method(rb_cArchiveEntry, "set_ctime", rb_libarchive_entry_set_ctime2, 2);
  rb_define_method(rb_cArchiveEntry, "unset_ctime", rb_libarchive_entry_unset_ctime, 0);
  rb_define_method(rb_cArchiveEntry, "dev=", rb_libarchive_entry_set_dev, 1);
  rb_define_method(rb_cArchiveEntry, "devmajor=", rb_libarchive_entry_set_devmajor, 1);
  rb_define_method(rb_cArchiveEntry, "devminor=", rb_libarchive_entry_set_devminor, 1);
  rb_define_method(rb_cArchiveEntry, "filetype=", rb_libarchive_entry_set_filetype, 1);
  rb_define_method(rb_cArchiveEntry, "set_fflags", rb_libarchive_entry_set_fflags, 2);
  rb_define_method(rb_cArchiveEntry, "copy_fflags_text", rb_libarchive_entry_copy_fflags_text, 1);
  rb_define_method(rb_cArchiveEntry, "gid=", rb_libarchive_entry_set_gid, 1);
  rb_define_method(rb_cArchiveEntry, "gname=", rb_libarchive_entry_set_gname, 1);
  rb_define_method(rb_cArchiveEntry, "copy_gname", rb_libarchive_entry_copy_gname, 1);
  rb_define_method(rb_cArchiveEntry, "hardlink=", rb_libarchive_entry_set_hardlink, 1);
  rb_define_method(rb_cArchiveEntry, "copy_hardlink", rb_libarchive_entry_copy_hardlink, 1);
  rb_define_method(rb_cArchiveEntry, "ino=", rb_libarchive_entry_set_ino, 1);
  rb_define_method(rb_cArchiveEntry, "link=", rb_libarchive_entry_set_link, 1);
  rb_define_method(rb_cArchiveEntry, "copy_link", rb_libarchive_entry_copy_link, 1);
  rb_define_method(rb_cArchiveEntry, "mode=", rb_libarchive_entry_set_mode, 1);
  rb_define_method(rb_cArchiveEntry, "mtime=", rb_libarchive_entry_set_mtime, 1);
  rb_define_method(rb_cArchiveEntry, "set_mtime", rb_libarchive_entry_set_mtime2, 2);
  rb_define_method(rb_cArchiveEntry, "unset_mtime", rb_libarchive_entry_unset_mtime, 0);
  rb_define_method(rb_cArchiveEntry, "nlink=", rb_libarchive_entry_set_nlink, 1);
  rb_define_method(rb_cArchiveEntry, "pathname=", rb_libarchive_entry_set_pathname, 1);
  rb_define_method(rb_cArchiveEntry, "copy_pathname", rb_libarchive_entry_copy_pathname, 1);
  rb_define_method(rb_cArchiveEntry, "perm=", rb_libarchive_entry_set_perm, 1);
  rb_define_method(rb_cArchiveEntry, "rdev=", rb_libarchive_entry_set_rdev, 1);
  rb_define_method(rb_cArchiveEntry, "rdevmajor=", rb_libarchive_entry_set_rdevmajor, 1);
  rb_define_method(rb_cArchiveEntry, "rdevminor=", rb_libarchive_entry_set_rdevminor, 1);
  rb_define_method(rb_cArchiveEntry, "size=", rb_libarchive_entry_set_size, 1);
  rb_define_method(rb_cArchiveEntry, "unset_size", rb_libarchive_entry_unset_size, 0);
#if ARCHIVE_VERSION_NUMBER >= 2005003
  rb_define_method(rb_cArchiveEntry, "copy_sourcepath", rb_libarchive_entry_copy_sourcepath, 1);
#endif
  rb_define_method(rb_cArchiveEntry, "symlink=", rb_libarchive_entry_set_symlink, 1);
  rb_define_method(rb_cArchiveEntry, "copy_symlink", rb_libarchive_entry_copy_symlink, 1);
  rb_define_method(rb_cArchiveEntry, "uid=", rb_libarchive_entry_set_uid, 1);
  rb_define_method(rb_cArchiveEntry, "uname=", rb_libarchive_entry_set_uname, 1);
  rb_define_method(rb_cArchiveEntry, "copy_uname", rb_libarchive_entry_copy_uname, 1);

  rb_define_method(rb_cArchiveEntry, "copy_stat", rb_libarchive_entry_copy_stat, 1);
  rb_define_method(rb_cArchiveEntry, "copy_lstat", rb_libarchive_entry_copy_lstat, 1);

  rb_define_method(rb_cArchiveEntry, "xattr_clear", rb_libarchive_entry_xattr_clear, 0);
  rb_define_method(rb_cArchiveEntry, "xattr_add_entry", rb_libarchive_entry_xattr_add_entry, 2);
  rb_define_method(rb_cArchiveEntry, "xattr_count", rb_libarchive_entry_xattr_count, 0);
  rb_define_method(rb_cArchiveEntry, "xattr_reset", rb_libarchive_entry_xattr_reset, 0);
  rb_define_method(rb_cArchiveEntry, "xattr_next", rb_libarchive_entry_xattr_next, 0);
}
#include "libarchive_internal.h"

extern VALUE rb_mArchive;
VALUE rb_cArchiveReader;
extern VALUE rb_eArchiveError;
extern VALUE rb_cArchiveEntry;

static void rb_libarchive_reader_close0(struct rb_libarchive_archive_container *p) {
  archive_read_close(p->ar);
  archive_read_finish(p->ar);
  p->ar = NULL;
}

/* */
static VALUE rb_libarchive_reader_close(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  rb_libarchive_reader_close0(p);
  return Qnil;
}

static VALUE rb_libarchive_reader_s_open0(int (*archive_open)(struct rb_libarchive_archive_container *, void *), void *arg, int compression, int format, const char *cmd) {
  VALUE reader;
  struct rb_libarchive_archive_container *p;
  int r;
  reader = rb_funcall(rb_cArchiveReader, rb_intern("new"), 0);
  Data_Get_Struct(reader, struct rb_libarchive_archive_container, p);

  if ((p->ar = archive_read_new()) == NULL) {
    rb_raise(rb_eArchiveError, "Open reader failed: %s", strerror(errno));
  }

  if (cmd != NULL) {
    r = archive_read_support_compression_program(p->ar, cmd);
  } else if (compression != -1) {
    r = archive_read_support_compression(p->ar, compression);
  } else {
    r = archive_read_support_compression_all(p->ar);
  }

  if (r != ARCHIVE_OK) {
    char error_string[BUFSIZ];
    archive_copy_error_string(p->ar, error_string, BUFSIZ);
    rb_libarchive_reader_close0(p);
    rb_raise(rb_eArchiveError, "Support compression failed: %s", error_string);
  }

  if (format != -1) {
    r = archive_read_support_format(p->ar, format);
  } else {
    r = archive_read_support_format_all(p->ar);
  }

  if (r != ARCHIVE_OK) {
    char error_string[BUFSIZ];
    archive_copy_error_string(p->ar, error_string, BUFSIZ);
    rb_libarchive_reader_close0(p);
    rb_raise(rb_eArchiveError, "Support format failed: %s", error_string);
  }

  if (archive_open(p, arg) != ARCHIVE_OK) {
    char error_string[BUFSIZ];
    archive_copy_error_string(p->ar, error_string, BUFSIZ);
    rb_libarchive_reader_close0(p);
    rb_raise(rb_eArchiveError, "Open reader failed: %s", error_string);
  }

  if (rb_block_given_p()) {
    VALUE retval;
    int status;
    retval = rb_protect(rb_yield, reader, &status);
    rb_libarchive_reader_close0(p);

    if (status != 0) {
      rb_jump_tag(status);
    }

    return retval;
  } else {
    return reader;
  }
}

static int rb_libarchive_reader_s_open_filename0(struct rb_libarchive_archive_container *p, void *arg) {
  const char *filename = (const char *) arg;

  if (filename != NULL) {
    struct stat s;

    if (stat(filename, &s) != 0) {
      archive_set_error(p->ar, -1, strerror(errno));
      return (ARCHIVE_FATAL);
    }
  }

  return archive_read_open_filename(p->ar, filename, BLOCK_SIZE);
}

/* */
static VALUE rb_libarchive_reader_s_open_filename(int argc, VALUE *argv, VALUE self) {
  VALUE v_filename, v_compression, v_format;
  const char *filename = NULL;
  int compression = -1, format = -1;
  const char *cmd = NULL;
  rb_scan_args(argc, argv, "12", &v_filename, &v_compression, &v_format);
  Check_Type(v_filename, T_STRING);
  filename = RSTRING_PTR(v_filename);

  if (T_STRING == TYPE(v_compression)) {
    compression = -1;
    cmd = RSTRING_PTR(v_compression);
  } else if (!NIL_P(v_compression)) {
    compression = NUM2INT(v_compression);
  }

  if (!NIL_P(v_format)) {
    format = NUM2INT(v_format);
  }

  return rb_libarchive_reader_s_open0(rb_libarchive_reader_s_open_filename0, (void *) filename, compression, format, cmd);
}

static int rb_libarchive_reader_s_open_memory0(struct rb_libarchive_archive_container *p, void *arg) {
  VALUE v_buff = (VALUE) arg;
  return archive_read_open_memory(p->ar, RSTRING_PTR(v_buff), RSTRING_LEN(v_buff));
}

/* */
static VALUE rb_libarchive_reader_s_open_memory(int argc, VALUE *argv, VALUE self) {
  VALUE v_memory, v_compression, v_format;
  int compression = -1, format = -1;
  const char *cmd = NULL;
  rb_scan_args(argc, argv, "12", &v_memory, &v_compression, &v_format);
  Check_Type(v_memory, T_STRING);

  if (T_STRING == TYPE(v_compression)) {
    compression = -1;
    cmd = RSTRING_PTR(v_compression);
  } else if (!NIL_P(v_compression)) {
    compression = NUM2INT(v_compression);
  }

  if (!NIL_P(v_format)) {
    format = NUM2INT(v_format);
  }

  return rb_libarchive_reader_s_open0(rb_libarchive_reader_s_open_memory0, (void *) v_memory, compression, format, cmd);
}

/* */
static VALUE rb_libarchive_reader_next_header(VALUE self) {
  struct rb_libarchive_archive_container *p;
  struct archive_entry *ae;
  int r;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);

  if (p->eof) {
    return Qnil;
  }

  r = archive_read_next_header(p->ar, &ae);

  if (r == ARCHIVE_EOF) {
    p->eof = 1;
    return Qnil;
  } else if (r != ARCHIVE_OK) {
    rb_raise(rb_eArchiveError, "Fetch entry failed: %s", archive_error_string(p->ar));
  }

  return rb_libarchive_entry_new(ae, 0);
}

/* */
static VALUE rb_libarchive_reader_header_position(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  return LONG2NUM((long) archive_read_header_position(p->ar));
}

/* */
static VALUE rb_libarchive_reader_read_data(int argc, VALUE *argv, VALUE self) {
  VALUE v_size;
  struct rb_libarchive_archive_container *p;
  char *buff;
  size_t size = DATA_BUFFER_SIZE;
  ssize_t n;
  rb_scan_args(argc, argv, "01", &v_size);

  if (!NIL_P(v_size)) {
    size = NUM2INT(v_size);
  }

  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);

  if (p->eof) {
    return Qnil;
  }

  if (rb_block_given_p()) {
    ssize_t len = 0;
    int status = 0;
    buff = xmalloc(size);

    while ((n = archive_read_data(p->ar, buff, size)) > 0) {
      rb_protect(rb_yield, rb_str_new(buff, n), &status);

      if (status != 0) {
        break;
      }

      len += n;
    }

    xfree(buff);

    if (status != 0) {
      rb_jump_tag(status);
    }

    if (n < 0) {
      rb_raise(rb_eArchiveError, "Read data failed: %s", archive_error_string(p->ar));
    }

    return LONG2NUM(len);
  } else {
    VALUE retval = rb_str_new("", 0);
    buff = xmalloc(size);

    while ((n = archive_read_data(p->ar, buff, size)) > 0) {
      rb_str_cat(retval, buff, n);
    }

    xfree(buff);

    if (n < 0) {
      rb_raise(rb_eArchiveError, "Read data failed: %s", archive_error_string(p->ar));
    }

    return retval;
  }
}

/* */
static VALUE rb_libarchive_reader_save_data(int argc, VALUE *argv, VALUE self) {
  VALUE v_filename, v_flags;
  struct rb_libarchive_archive_container *p;
  const char *filename;
  int flags, fd, r;
  rb_scan_args(argc, argv, "11", &v_filename, &v_flags);
  Check_Type(v_filename, T_STRING);
  filename = RSTRING_PTR(v_filename);

  if (!NIL_P(v_flags)) {
    flags = ((O_WRONLY | NUM2INT(v_flags)) & O_FLAGS);
  } else {
    flags = (O_WRONLY | O_CREAT | O_EXCL
#ifdef O_BINARY
             | O_BINARY
#endif
             );
  }

  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);

  if ((fd = open(filename, flags)) == -1) {
    rb_raise(rb_eArchiveError, "Save data failed: %s", strerror(errno));
  }

  r = archive_read_data_into_fd(p->ar, fd);
  _close(fd);

  if (r != ARCHIVE_OK) {
    rb_raise(rb_eArchiveError, "Save data failed: %s", archive_error_string(p->ar));
  }

  return Qnil;
}

/* */
static VALUE rb_libarchive_reader_extract(int argc, VALUE *argv, VALUE self) {
  VALUE v_entry, v_flags;
  struct rb_libarchive_archive_container *pa;
  struct rb_libarchive_entry_container *pae;
  int flags = 0;
  rb_scan_args(argc, argv, "11", &v_entry, &v_flags);
  Check_Class(v_entry, rb_cArchiveEntry);

  if (!NIL_P(v_flags)) {
    flags = (NUM2INT(v_flags) & EXTRACT_FLAGS);
  }

  Data_Get_Struct(self, struct rb_libarchive_archive_container, pa);
  Check_Archive(pa);

  if (pa->eof) {
    rb_raise(rb_eArchiveError, "Extract archive failed: It has already reached EOF");
  }

  Data_Get_Struct(v_entry, struct rb_libarchive_entry_container, pae);
  Check_Entry(pae);

  if (archive_read_extract(pa->ar, pae->ae, flags) != ARCHIVE_OK) {
    rb_raise(rb_eArchiveError, "Extract archive failed: %s", archive_error_string(pa->ar));
  }

  return Qnil;
}

void Init_libarchive_reader() {
  rb_cArchiveReader = rb_define_class_under(rb_mArchive, "Reader", rb_cObject);
  rb_define_alloc_func(rb_cArchiveReader, rb_libarchive_archive_alloc);
  rb_funcall(rb_cArchiveReader, rb_intern("private_class_method"), 1, ID2SYM(rb_intern("new")));
  rb_define_singleton_method(rb_cArchiveReader, "open_filename", rb_libarchive_reader_s_open_filename, -1);
  rb_define_module_function(rb_mArchive, "read_open_filename", rb_libarchive_reader_s_open_filename, -1);
  rb_define_singleton_method(rb_cArchiveReader, "open_memory", rb_libarchive_reader_s_open_memory, -1);
  rb_define_module_function(rb_mArchive, "read_open_memory", rb_libarchive_reader_s_open_memory, -1);
  rb_define_method(rb_cArchiveReader, "close", rb_libarchive_reader_close, 0);
  rb_define_method(rb_cArchiveReader, "next_header", rb_libarchive_reader_next_header, 0);
  rb_define_method(rb_cArchiveReader, "header_position", rb_libarchive_reader_header_position, 0);
  rb_define_method(rb_cArchiveReader, "read_data", rb_libarchive_reader_read_data, -1);
  rb_define_method(rb_cArchiveReader, "save_data", rb_libarchive_reader_save_data, -1);
  rb_define_method(rb_cArchiveReader, "extract", rb_libarchive_reader_extract, -1);
}
#include "libarchive_internal.h"

extern VALUE rb_mArchive;
VALUE rb_cArchiveWriter;
extern VALUE rb_eArchiveError;
extern VALUE rb_cArchiveEntry;

static void rb_libarchive_writer_close0(struct rb_libarchive_archive_container *p) {
  archive_write_close(p->ar);
  archive_write_finish(p->ar);
  p->ar = NULL;
}

/* */
static VALUE rb_libarchive_writer_close(VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);
  rb_libarchive_writer_close0(p);
  return Qnil;
}

static VALUE rb_libarchive_writer_s_open0(int (*archive_open)(struct rb_libarchive_archive_container *, void *), void *arg, int compression, int format, const char *cmd) {
  VALUE writer;
  struct rb_libarchive_archive_container *p;
  int r;
  writer = rb_funcall(rb_cArchiveWriter, rb_intern("new"), 0);
  Data_Get_Struct(writer, struct rb_libarchive_archive_container, p);

  if ((p->ar = archive_write_new()) == NULL) {
    rb_raise(rb_eArchiveError, "Open writer failed: %s", strerror(errno));
  }

  if (cmd != NULL) {
    r = archive_write_set_compression_program(p->ar,  cmd);
  } else {
    r = archive_write_set_compression(p->ar, compression);
  }

  if (r != ARCHIVE_OK) {
    char error_string[BUFSIZ];
    archive_copy_error_string(p->ar, error_string, BUFSIZ);
    rb_libarchive_writer_close0(p);
    rb_raise(rb_eArchiveError, "Set compression failed: %s", error_string);
  }

  if (archive_write_set_format(p->ar, format) != ARCHIVE_OK) {
    char error_string[BUFSIZ];
    archive_copy_error_string(p->ar, error_string, BUFSIZ);
    rb_libarchive_writer_close0(p);
    rb_raise(rb_eArchiveError, "Set format failed: %s", error_string);
  }

  if (archive_open(p, arg) != ARCHIVE_OK) {
    char error_string[BUFSIZ];
    archive_copy_error_string(p->ar, error_string, BUFSIZ);
    rb_libarchive_writer_close0(p);
    rb_raise(rb_eArchiveError, "Open writer failed: %s", error_string);
  }

  if (rb_block_given_p()) {
    VALUE retval;
    int status;
    retval = rb_protect(rb_yield, writer, &status);
    rb_libarchive_writer_close0(p);

    if (status != 0) {
      rb_jump_tag(status);
    }

    return retval;
  } else {
    return writer;
  }
}

static int rb_libarchive_writer_s_open_filename0(struct rb_libarchive_archive_container *p, void *arg) {
  const char *filename = (const char *) arg;
  return archive_write_open_filename(p->ar, filename);
}

/* */
static VALUE rb_libarchive_writer_s_open_filename(VALUE self, VALUE v_filename, VALUE v_compression, VALUE v_format) {
  const char *filename = NULL;
  int compression, format;
  const char *cmd = NULL;
  Check_Type(v_filename, T_STRING);

  if (RSTRING_LEN(v_filename) < 1) {
    rb_raise(rb_eArchiveError, "Open writer failed: No such file or directory");
  }

  filename = RSTRING_PTR(v_filename);

  if (T_STRING == TYPE(v_compression)) {
    compression = -1;
    cmd = RSTRING_PTR(v_compression);
  } else {
    compression = NUM2INT(v_compression);
  }


  format = NUM2INT(v_format);
  return rb_libarchive_writer_s_open0(rb_libarchive_writer_s_open_filename0, (void *) filename, compression, format, cmd);
}

static int rb_libarchive_writer_s_open_memory0(struct rb_libarchive_archive_container *p, void *arg) {
  VALUE str = (VALUE) arg;
  p->memory = str;
  return archive_write_open_rb_str(p->ar, str);
}

/* */
static VALUE rb_libarchive_writer_s_open_memory(VALUE self, VALUE v_memory, VALUE v_compression, VALUE v_format) {
  int compression, format;
  const char *cmd = NULL;
  Check_Type(v_memory, T_STRING);

  if (T_STRING == TYPE(v_compression)) {
    compression = -1;
    cmd = RSTRING_PTR(v_compression);
  } else {
    compression = NUM2INT(v_compression);
  }

  format = NUM2INT(v_format);
  return rb_libarchive_writer_s_open0(rb_libarchive_writer_s_open_memory0, (void *) v_memory, compression, format, cmd);
}

/* */
static VALUE rb_libarchive_writer_new_entry(VALUE self) {
  VALUE entry;
  struct rb_libarchive_archive_container *p;
  struct archive_entry *ae;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);

  if ((ae = archive_entry_new()) == NULL) {
    rb_raise(rb_eArchiveError, "New entry failed: %s", strerror(errno));
  }

  entry = rb_libarchive_entry_new(ae, 1);

  if (rb_block_given_p()) {
    VALUE retval;
    int status;
    retval = rb_protect(rb_yield, entry, &status);
    rb_libarchive_entry_close(entry);

    if (status != 0) {
      rb_jump_tag(status);
    }

    return retval;
  } else {
    return entry;
  }
}

/* */
static VALUE rb_libarchive_writer_write_header(VALUE self, VALUE v_entry) {
  struct rb_libarchive_archive_container *pa;
  struct rb_libarchive_entry_container *pae;
  Check_Class(v_entry, rb_cArchiveEntry);
  Data_Get_Struct(self, struct rb_libarchive_archive_container, pa);
  Check_Archive(pa);
  Data_Get_Struct(v_entry, struct rb_libarchive_entry_container, pae);
  Check_Entry(pae);

  if (archive_write_header(pa->ar, pae->ae) != ARCHIVE_OK) {
    rb_raise(rb_eArchiveError, "Write header failed: %s", archive_error_string(pa->ar));
  }

  return Qnil;
}

static ssize_t rb_libarchive_writer_write_data0(struct archive *ar, VALUE v_buff) {
  const char *buff;
  size_t size;
  ssize_t n;

  if (NIL_P(v_buff)) {
    return 0;
  }

  Check_Type(v_buff, T_STRING);
  buff = RSTRING_PTR(v_buff);
  size = RSTRING_LEN(v_buff);

  if (size < 1) {
    return 0;
  }

  if ((n = archive_write_data(ar, buff, size)) < 0) {
    rb_raise(rb_eArchiveError, "Write data failed: %s", archive_error_string(ar));
  }

  return n;
}

/* */
static VALUE rb_libarchive_writer_write_data(int argc, VALUE *argv, VALUE self) {
  struct rb_libarchive_archive_container *p;
  Data_Get_Struct(self, struct rb_libarchive_archive_container, p);
  Check_Archive(p);

  if (rb_block_given_p()) {
    ssize_t len = 0;

    if (argc > 0) {
      rb_raise(rb_eArgError, "wrong number of arguments (%d for 0)", argc);
    }

    while(1) {
      VALUE retval;
      ssize_t n;
      retval = rb_yield(Qnil);

      if ((n = rb_libarchive_writer_write_data0(p->ar, retval)) < 1) {
        return LONG2NUM(len);
      }

      len += n;
    }
  } else {
    VALUE v_buff;
    ssize_t n;
    rb_scan_args(argc, argv, "10", &v_buff);
    n = rb_libarchive_writer_write_data0(p->ar, v_buff);
    return LONG2NUM(n);
  }
}

void Init_libarchive_writer() {
  rb_cArchiveWriter = rb_define_class_under(rb_mArchive, "Writer", rb_cObject);
  rb_define_alloc_func(rb_cArchiveWriter, rb_libarchive_archive_alloc);
  rb_funcall(rb_cArchiveWriter, rb_intern("private_class_method"), 1, ID2SYM(rb_intern("new")));
  rb_define_singleton_method(rb_cArchiveWriter, "open_filename", rb_libarchive_writer_s_open_filename, 3);
  rb_define_singleton_method(rb_mArchive, "write_open_filename", rb_libarchive_writer_s_open_filename, 3);
  rb_define_singleton_method(rb_cArchiveWriter, "open_memory", rb_libarchive_writer_s_open_memory, 3);
  rb_define_singleton_method(rb_mArchive, "write_open_memory", rb_libarchive_writer_s_open_memory, 3);
  rb_define_method(rb_cArchiveWriter, "close", rb_libarchive_writer_close, 0);
  rb_define_method(rb_cArchiveWriter, "new_entry", rb_libarchive_writer_new_entry, 0);
  rb_define_method(rb_cArchiveWriter, "write_header", rb_libarchive_writer_write_header, 1);
  rb_define_method(rb_cArchiveWriter, "write_data", rb_libarchive_writer_write_data, -1);
}
