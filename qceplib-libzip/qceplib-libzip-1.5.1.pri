message(qceplib-libzip PWD = $${PWD} QCEPLIB_LIBZIP_VERSION = $${QCEPLIB_LIBZIP_VERSION})

include(qceplib-libzip-include-$${QCEPLIB_LIBZIP_VERSION}.pri)

DEFINES +=
HEADERS += \
  $$LIBZIPBASE/zip.h \
  $$LIBZIPBASE/compat.h \
  $$LIBZIPCONF/config.h \
  $$LIBZIPCONF/zipconf.h

SOURCES += \
  $$LIBZIPBASE/zip_add.c \
  $$LIBZIPBASE/zip_add_dir.c \
  $$LIBZIPBASE/zip_add_entry.c \
  $$LIBZIPBASE/zip_algorithm_bzip2.c \
  $$LIBZIPBASE/zip_algorithm_deflate.c \
  $$LIBZIPBASE/zip_buffer.c \
  $$LIBZIPBASE/zip_close.c \
#  $$LIBZIPBASE/zip_crypto_commoncrypto.c \
#  $$LIBZIPBASE/zip_crypto_gnutls.c \
#  $$LIBZIPBASE/zip_crypto_openssl.c \
  $$LIBZIPBASE/zip_delete.c \
  $$LIBZIPBASE/zip_dir_add.c \
  $$LIBZIPBASE/zip_dirent.c \
  $$LIBZIPBASE/zip_discard.c \
  $$LIBZIPBASE/zip_entry.c \
  $$LIBZIPBASE/zip_error.c \
  $$LIBZIPBASE/zip_error_clear.c \
  $$LIBZIPBASE/zip_error_get.c \
  $$LIBZIPBASE/zip_error_get_sys_type.c \
  $$LIBZIPBASE/zip_error_strerror.c \
  $$LIBZIPBASE/zip_error_to_str.c \
  $$LIBZIPBASE/zip_err_str.c \
  $$LIBZIPBASE/zip_extra_field_api.c \
  $$LIBZIPBASE/zip_extra_field.c \
  $$LIBZIPBASE/zip_fclose.c \
  $$LIBZIPBASE/zip_fdopen.c \
  $$LIBZIPBASE/zip_file_add.c \
  $$LIBZIPBASE/zip_file_error_clear.c \
  $$LIBZIPBASE/zip_file_error_get.c \
  $$LIBZIPBASE/zip_file_get_comment.c \
  $$LIBZIPBASE/zip_file_get_external_attributes.c \
  $$LIBZIPBASE/zip_file_get_offset.c \
  $$LIBZIPBASE/zip_filerange_crc.c \
  $$LIBZIPBASE/zip_file_rename.c \
  $$LIBZIPBASE/zip_file_replace.c \
  $$LIBZIPBASE/zip_file_set_comment.c \
  $$LIBZIPBASE/zip_file_set_encryption.c \
  $$LIBZIPBASE/zip_file_set_external_attributes.c \
  $$LIBZIPBASE/zip_file_set_mtime.c \
  $$LIBZIPBASE/zip_file_strerror.c \
  $$LIBZIPBASE/zip_fopen.c \
  $$LIBZIPBASE/zip_fopen_encrypted.c \
  $$LIBZIPBASE/zip_fopen_index.c \
  $$LIBZIPBASE/zip_fopen_index_encrypted.c \
  $$LIBZIPBASE/zip_fread.c \
  $$LIBZIPBASE/zip_fseek.c \
  $$LIBZIPBASE/zip_ftell.c \
  $$LIBZIPBASE/zip_get_archive_comment.c \
  $$LIBZIPBASE/zip_get_archive_flag.c \
  $$LIBZIPBASE/zip_get_encryption_implementation.c \
  $$LIBZIPBASE/zip_get_file_comment.c \
  $$LIBZIPBASE/zip_get_name.c \
  $$LIBZIPBASE/zip_get_num_entries.c \
  $$LIBZIPBASE/zip_get_num_files.c \
  $$LIBZIPBASE/zip_hash.c \
  $$LIBZIPBASE/zip_io_util.c \
  $$LIBZIPBASE/zip_libzip_version.c \
  $$LIBZIPBASE/zip_memdup.c \
  $$LIBZIPBASE/zip_name_locate.c \
  $$LIBZIPBASE/zip_new.c \
  $$LIBZIPBASE/zip_open.c \
  $$LIBZIPBASE/zip_progress.c \
  $$LIBZIPBASE/zip_random_unix.c \
#  $$LIBZIPBASE/zip_random_uwp.c \
#  $$LIBZIPBASE/zip_random_win32.c \
  $$LIBZIPBASE/zip_rename.c \
  $$LIBZIPBASE/zip_replace.c \
  $$LIBZIPBASE/zip_set_archive_comment.c \
  $$LIBZIPBASE/zip_set_archive_flag.c \
  $$LIBZIPBASE/zip_set_default_password.c \
  $$LIBZIPBASE/zip_set_file_comment.c \
  $$LIBZIPBASE/zip_set_file_compression.c \
  $$LIBZIPBASE/zip_set_name.c \
  $$LIBZIPBASE/zip_source_begin_write.c \
  $$LIBZIPBASE/zip_source_begin_write_cloning.c \
  $$LIBZIPBASE/zip_source_buffer.c \
  $$LIBZIPBASE/zip_source_call.c \
  $$LIBZIPBASE/zip_source_close.c \
  $$LIBZIPBASE/zip_source_commit_write.c \
  $$LIBZIPBASE/zip_source_compress.c \
  $$LIBZIPBASE/zip_source_crc.c \
  $$LIBZIPBASE/zip_source_error.c \
  $$LIBZIPBASE/zip_source_file.c \
  $$LIBZIPBASE/zip_source_filep.c \
  $$LIBZIPBASE/zip_source_free.c \
  $$LIBZIPBASE/zip_source_function.c \
  $$LIBZIPBASE/zip_source_get_compression_flags.c \
  $$LIBZIPBASE/zip_source_is_deleted.c \
  $$LIBZIPBASE/zip_source_layered.c \
  $$LIBZIPBASE/zip_source_open.c \
  $$LIBZIPBASE/zip_source_pkware.c \
  $$LIBZIPBASE/zip_source_read.c \
  $$LIBZIPBASE/zip_source_remove.c \
  $$LIBZIPBASE/zip_source_rollback_write.c \
  $$LIBZIPBASE/zip_source_seek.c \
  $$LIBZIPBASE/zip_source_seek_write.c \
  $$LIBZIPBASE/zip_source_stat.c \
  $$LIBZIPBASE/zip_source_supports.c \
  $$LIBZIPBASE/zip_source_tell.c \
  $$LIBZIPBASE/zip_source_tell_write.c \
#  $$LIBZIPBASE/zip_source_win32a.c \
#  $$LIBZIPBASE/zip_source_win32handle.c \
#  $$LIBZIPBASE/zip_source_win32utf8.c \
#  $$LIBZIPBASE/zip_source_win32w.c \
  $$LIBZIPBASE/zip_source_window.c \
#  $$LIBZIPBASE/zip_source_winzip_aes_decode.c \
#  $$LIBZIPBASE/zip_source_winzip_aes_encode.c \
  $$LIBZIPBASE/zip_source_write.c \
  $$LIBZIPBASE/zip_source_zip.c \
  $$LIBZIPBASE/zip_source_zip_new.c \
  $$LIBZIPBASE/zip_stat.c \
  $$LIBZIPBASE/zip_stat_index.c \
  $$LIBZIPBASE/zip_stat_init.c \
  $$LIBZIPBASE/zip_strerror.c \
  $$LIBZIPBASE/zip_string.c \
  $$LIBZIPBASE/zip_unchange_all.c \
  $$LIBZIPBASE/zip_unchange_archive.c \
  $$LIBZIPBASE/zip_unchange.c \
  $$LIBZIPBASE/zip_unchange_data.c \
  $$LIBZIPBASE/zip_utf-8.c \
#  $$LIBZIPBASE/zip_winzip_aes.c
