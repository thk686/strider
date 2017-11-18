context("test-strider.R")

test_that("row_sums are correct", {
  x = matrix(1:9, 3)
  expect_equal(row_sums(x), rowSums(x))
})

test_that("col_sums are correct", {
  x = matrix(1:9, 3)
  expect_equal(col_sums(x), colSums(x))
})

test_that("convolve2 is correct", {
  a = matrix(c(1, 2, 1,
               1, 1, 1), 2, 3, byrow = TRUE)
  b = matrix(c(0, 0, 0,
               0, 0, 0,
               0, 1, 0,
               0, 0, 0), 4, 3, byrow = TRUE)
  expect_identical(t(convolve2(a, b)), convolve2(t(a), t(b)))
})
