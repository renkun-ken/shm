library(data.table)
library(shm)

file <- "/auto/chinaqr/shared/forKen/sxm_prod/sxm_stats.fst"
system.time(sxm <- fst::read_fst(file, as.data.table = TRUE))
system.time(copy(sxm))

system.time({
  shm_remove_segment("sxm")
  shm_create_segment("sxm", 1024^3)
  shm_set_list(sxm, "sxm", threads = 10)
})

system.time(fst::write_fst(sxm, "/dev/shm/data_test/data.fst", compress = 0))

system.time({
  shm_remove_segment("sxm")
  shm_create_segment("sxm", 1024^4)
  for (col in names(sxm)) {
    shm_set(sxm[[col]], "sxm", col)
  }
})
