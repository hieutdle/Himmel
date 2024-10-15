.PHONY: format test clean build

# The build directory
BUILD_DIR = build

# Build the project
build:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake .. && cmake --build .
	@echo "Build complete."

# Run all tests using CTest
test:
	@echo "Running tests..."
	@cd $(BUILD_DIR) && ctest -V
	@echo "All tests passed."

# Format the code (using clang-format)
format:
	@echo "Formatting code..."
	@clang-format -i src/*.cc include/*.h test/*.cc
	@echo "Code formatted."

# Clean the build directory
clean:
	@rm -rf $(BUILD_DIR)
	@echo "Build directory cleaned."
