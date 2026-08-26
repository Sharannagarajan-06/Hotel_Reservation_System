//
// Created by asus on 8/26/2026.
//

#include <gtest/gtest.h>
#include <memory>
#include "models/user_details.h"
#include "models/guest_details.h"
#include "models/admin_details.h"

class UserTest : public ::testing::Test
{
protected:
    std::string name = "Sharan";
    std::string phone = "9345480377";
    std::string email = "sharan@gmail.com";
};

TEST_F(UserTest, GuestCanBeCreated)
{
    EXPECT_NO_THROW({
        GuestDetails guest(
            name,
            phone,
            email);
    });
}

TEST_F(UserTest, GuestStoresCorrectName)
{
    GuestDetails guest(
        name,
        phone,
        email);

    EXPECT_EQ(guest.getUserName(), name);
}

TEST_F(UserTest, GuestStoresCorrectPhoneNumber)
{
    GuestDetails guest(
        name,
        phone,
        email);

    EXPECT_EQ(
        guest.getUserPhoneNumber(),
        phone);
}

TEST_F(UserTest, GuestStoresCorrectEmail)
{
    GuestDetails guest(
        name,
        phone,
        email);

    EXPECT_EQ(
        guest.getUserEmail(),
        email);
}

TEST_F(UserTest, GuestGetsValidUserId)
{
    GuestDetails guest(
        name,
        phone,
        email);

    EXPECT_GT(
        guest.getUserId(),
        0);
}

TEST_F(UserTest, DifferentGuestsHaveDifferentIds)
{
    GuestDetails guest1(
        name,
        phone,
        email);

    GuestDetails guest2(
        "Kumar",
        "9876543210",
        "kumar@gmail.com");

    EXPECT_NE(
        guest1.getUserId(),
        guest2.getUserId());
}

TEST_F(UserTest, AdminCanBeCreated)
{
    EXPECT_NO_THROW({
        AdminDetails admin(
            name,
            phone,
            "admin@gmail.com",
            "123");
    });
}

TEST_F(UserTest, AdminStoresCorrectName)
{
    AdminDetails admin(
        name,
        phone,
        "admin@gmail.com",
        "123");

    EXPECT_EQ(
        admin.getUserName(),
        name);
}

TEST_F(UserTest, AdminStoresCorrectEmail)
{
    AdminDetails admin(
        name,
        phone,
        "admin@gmail.com",
        "123");

    EXPECT_EQ(
        admin.getUserEmail(),
        "admin@gmail.com");
}

TEST_F(UserTest, AdminGetsValidUserId)
{
    AdminDetails admin(
        name,
        phone,
        "admin@gmail.com",
        "123");

    EXPECT_GT(
        admin.getUserId(),
        0);
}

TEST_F(UserTest, GuestAndAdminHaveDifferentIds)
{
    GuestDetails guest(
        name,
        phone,
        email);

    AdminDetails admin(
        name,
        phone,
        "admin@gmail.com",
        "123");

    EXPECT_NE(
        guest.getUserId(),
        admin.getUserId());
}

TEST_F(UserTest, GuestCanBeStoredUsingBaseClassPointer)
{
    std::unique_ptr<UserDetails> user =
        std::make_unique<GuestDetails>(
            name,
            phone,
            email);

    ASSERT_NE(user, nullptr);

    EXPECT_EQ(
        user->getUserName(),
        name);
}

TEST_F(UserTest, AdminCanBeStoredUsingBaseClassPointer)
{
    std::unique_ptr<UserDetails> user =
        std::make_unique<AdminDetails>(
            name,
            phone,
            "admin@gmail.com",
            "123");

    ASSERT_NE(user, nullptr);

    EXPECT_EQ(
        user->getUserName(),
        name);
}