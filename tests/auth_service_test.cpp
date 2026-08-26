#include <gtest/gtest.h>
#include <memory>

#include "services/auth_service.h"
#include "models/hotel.h"
#include "models/guest_details.h"
#include "models/admin_details.h"
#include "exceptions/user_exception.h"

class AuthTest : public ::testing::Test
{

protected:
    Hotel hotel;
    std::unique_ptr<AuthService> authService;

    void SetUp() override
    {

        auto guest = std::make_unique<GuestDetails>(
            "Sharan",
            "9345480377",
            "sharan@gmail.com",
            "guest@123");

        auto admin = std::make_unique<AdminDetails>(
            "Admin",
            "9876543210",
            "admin@gmail.com",
            "123");

        hotel.adduser(std::move(guest));
        hotel.adduser(std::move(admin));

        authService = std::make_unique<AuthService>(hotel);
    }
};

TEST_F(AuthTest, ValidGuestLoginReturnsUser)
{

    UserDetails *user =
        authService->login(
            "sharan@gmail.com",
            "guest@123");

    ASSERT_NE(user, nullptr);

    EXPECT_EQ(
        user->getUserEmail(),
        "sharan@gmail.com");
}

TEST_F(AuthTest, ValidAdminLoginReturnsUser)
{

    UserDetails *user =
        authService->login(
            "admin@gmail.com",
            "123");

    ASSERT_NE(user, nullptr);

    EXPECT_EQ(
        user->getUserEmail(),
        "admin@gmail.com");
}

TEST_F(AuthTest, InvalidEmailThrowsException)
{

    EXPECT_THROW(
        authService->login(
            "wrong@gmail.com",
            "guest@123"),
        AuthenticationException);
}

TEST_F(AuthTest, InvalidPasswordThrowsException)
{

    EXPECT_THROW(
        authService->login(
            "sharan@gmail.com",
            "wrongpassword"),
        AuthenticationException);
}

TEST_F(AuthTest, InvalidEmailAndPasswordThrowsException)
{

    EXPECT_THROW(
        authService->login(
            "wrong@gmail.com",
            "wrongpassword"),
        AuthenticationException);
}

TEST_F(AuthTest, EmptyEmailThrowsException)
{

    EXPECT_THROW(
        authService->login(
            "",
            "guest@123"),
        AuthenticationException);
}

TEST_F(AuthTest, EmptyPasswordThrowsException)
{

    EXPECT_THROW(
        authService->login(
            "sharan@gmail.com",
            ""),
        AuthenticationException);
}

TEST_F(AuthTest, AdminIsRecognizedAsAdmin)
{

    UserDetails *user =
        authService->login(
            "admin@gmail.com",
            "123");

    ASSERT_NE(user, nullptr);

    EXPECT_TRUE(
        authService->isAdmin(user));
}

TEST_F(AuthTest, GuestIsNotRecognizedAsAdmin)
{

    UserDetails *user =
        authService->login(
            "sharan@gmail.com",
            "guest@123");

    ASSERT_NE(user, nullptr);

    EXPECT_FALSE(
        authService->isAdmin(user));
}
TEST_F(AuthTest, LoginReturnsCorrectUser)
{

    UserDetails *user =
        authService->login(
            "sharan@gmail.com",
            "guest@123");

    ASSERT_NE(user, nullptr);

    EXPECT_EQ(
        user->getUserName(),
        "Sharan");

    EXPECT_EQ(
        user->getUserEmail(),
        "sharan@gmail.com");

    EXPECT_EQ(
        user->getUserPhoneNumber(),
        "9345480377");
}

TEST_F(AuthTest, DifferentUsersCanLoginIndependently)
{

    UserDetails *guest =
        authService->login(
            "sharan@gmail.com",
            "guest@123");

    UserDetails *admin =
        authService->login(
            "admin@gmail.com",
            "123");

    ASSERT_NE(guest, nullptr);
    ASSERT_NE(admin, nullptr);

    EXPECT_NE(
        guest->getUserId(),
        admin->getUserId());

    EXPECT_FALSE(
        authService->isAdmin(guest));

    EXPECT_TRUE(
        authService->isAdmin(admin));
}

TEST_F(AuthTest, WrongPasswordDoesNotAuthenticateAdmin)
{

    EXPECT_THROW(
        authService->login(
            "admin@gmail.com",
            "wrong"),
        AuthenticationException);
}

TEST_F(AuthTest, WrongPasswordDoesNotAuthenticateGuest)
{

    EXPECT_THROW(
        authService->login(
            "sharan@gmail.com",
            "wrong"),
        AuthenticationException);
}
