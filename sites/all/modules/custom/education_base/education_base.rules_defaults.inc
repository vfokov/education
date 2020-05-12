<?php

/**
 * @file
 * education_base.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function education_base_default_rules_configuration() {
  $items = array();
  $items['rules_booking_email_to_user'] = entity_import('rules_config', '{ "rules_booking_email_to_user" : {
      "LABEL" : "Booking email to user",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Booking" ],
      "REQUIRES" : [ "rules", "mimemail", "education_common" ],
      "ON" : { "education_common_send_message_to_user" : [] },
      "DO" : [
        { "mimemail" : {
            "USING" : {
              "key" : "booking_email_to_user",
              "to" : "[email:value]",
              "from_name" : "[site:mail]",
              "subject" : "Booking a lesson",
              "body" : "Booking \\u2116 [order-id:value] \\u003Cbr \\/\\u003E\\r\\nUser name: [name:value] \\u003Cbr \\/\\u003E\\r\\nPhone: [phone:value] \\u003Cbr \\/\\u003E\\r\\nSkype: [skype:value] \\u003Cbr \\/\\u003E\\r\\n\\r\\n[order-mail-data:value]",
              "language" : [ "" ]
            },
            "PROVIDE" : { "send_status" : { "send_status" : "Send status" } }
          }
        },
        { "mimemail" : {
            "USING" : {
              "key" : "teacher_booking_notification",
              "to" : "[teacher-email:value]",
              "from_name" : "[site:mail]",
              "subject" : "Booking lesson notification",
              "body" : "Booking \\u2116 [order-id:value] \\u003Cbr \\/\\u003E\\r\\nUser name: [name:value] \\u003Cbr \\/\\u003E\\r\\nPhone: [phone:value] \\u003Cbr \\/\\u003E\\r\\nSkype: [skype:value] \\u003Cbr \\/\\u003E",
              "language" : [ "" ]
            },
            "PROVIDE" : { "send_status" : { "send_notification_status" : "Send status" } }
          }
        }
      ]
    }
  }');
  $items['rules_send_mail_accpunt_data_when_anonymous_bookig'] = entity_import('rules_config', '{ "rules_send_mail_accpunt_data_when_anonymous_bookig" : {
      "LABEL" : "Send mail account data when anonymous bookig",
      "PLUGIN" : "reaction rule",
      "OWNER" : "rules",
      "TAGS" : [ "Booking" ],
      "REQUIRES" : [ "rules", "education_common" ],
      "ON" : { "education_common_send_new_user_account_data" : [] },
      "DO" : [
        { "mail" : {
            "to" : "[email:value]",
            "subject" : "Created an account for you at [site:name] while booking a lesson",
            "message" : "Dear [name:value]!\\r\\n\\r\\nAn account at [site:name] has been created for you. You may now log in by clicking this link or copying and pasting it to your browser:\\r\\n\\r\\n[one-time-login:value]\\r\\n\\r\\nThis link can only be used once to log in and will lead you to a page where you can set your password.\\r\\n\\r\\nAfter setting your password, you will be able to log in at [site:login-url] in the future using:\\r\\n\\r\\nusername: [name:value]\\r\\npassword: Your password\\r\\n\\r\\n--  [site:name] team",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  return $items;
}
