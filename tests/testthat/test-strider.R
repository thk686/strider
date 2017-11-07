context("test-strider.R")

test_that("row_sums are correct", {
  x = matrix(1:9, 3)
  expect_equal(row_sums(x), rowSums(x))
})

test_that("col_sums are correct", {
  x = matrix(1:9, 3)
  expect_equal(col_sums(x), colSums(x))
})

test_that("will throw on error", {
  expect_error(test_throw_equal())
  expect_error(test_throw_distance1())
  expect_error(test_throw_distance2())
})
