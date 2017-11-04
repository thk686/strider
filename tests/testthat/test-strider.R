context("test-strider.R")

test_that("row_sums are correct", {
  x = matrix(1:9, 3)
  expect_equal(row_sums(x), rowSums(x))
})

test_that("col_sums are correct", {
  x = matrix(1:9, 3)
  expect_equal(col_sums(x), colSums(x))
})
